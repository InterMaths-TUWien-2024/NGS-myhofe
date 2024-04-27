/*

My own FESpace for high order finite elements

*/


#include <comp.hpp>

#include "myhoelement.hpp"
#include "myhofespace.hpp"


namespace ngcomp
{

  MyHighOrderFESpace :: MyHighOrderFESpace (shared_ptr<MeshAccess> ama, const Flags & flags)
    : FESpace (ama, flags)
  {
    type = "myhofespace";

    // Get the order from the flags, default is 2
    order = int(flags.GetNumFlag ("order", 2));

    evaluator[VOL] = make_shared<T_DifferentialOperator<DiffOpId<2>>>();
    flux_evaluator[VOL] = make_shared<T_DifferentialOperator<DiffOpGradient<2>>>();
    evaluator[BND] = make_shared<T_DifferentialOperator<DiffOpId<2>>>();
  }
    
  void MyHighOrderFESpace :: Update()
  {
    // some global update:

    int n_vert = ma->GetNV();  
    int n_edge = ma->GetNEdges(); 
    int n_face = ma->GetNFaces();  

    first_edge_dof.SetSize (n_edge+1);
    int ii = n_vert;
    for (int i = 0; i < n_edge; i++)
      {
        first_edge_dof[i] = ii;
        ii+=order-1;
      }
    first_edge_dof[n_edge] = ii;
      
    first_face_dof.SetSize (n_face+1);
    for (int i = 0; i < n_face; i++)
      {
        first_face_dof[i] = ii;
        if (ma->GetFaceType(i) == ET_TRIG)
          ii+=(order-1)*(order-2)/2;
        if (ma->GetFaceType(i) == ET_QUAD)
          ii+=(order-1)*(order-1);
      }
    first_face_dof[n_face] = ii;

    // cout << "first_edge_dof = " << endl << first_edge_dof << endl;
    // cout << "first_face_dof = " << endl << first_face_dof << endl;

    SetNDof (ii);
  }

  void MyHighOrderFESpace :: GetDofNrs (ElementId ei, Array<DofId> & dnums) const
  {
    // returns dof-numbers of element ei
    dnums.SetSize(0);
    auto ngel = ma->GetElement (ei);

    // vertex dofs
    for (auto v : ngel.Vertices())
      dnums.Append(v);

    // edge dofs
    for (auto e : ngel.Edges())
      for(int i = first_edge_dof[e]; i < first_edge_dof[e+1]; i++)
        dnums.Append (i);

    // face dofs
    for (auto f : ngel.Faces())
      for(int i = first_face_dof[ei.Nr()]; i < first_face_dof[ei.Nr()+1]; i++)
        dnums.Append (i);
  }

  
  FiniteElement & MyHighOrderFESpace :: GetFE (ElementId ei, Allocator & alloc) const
  {
    auto ngel = ma->GetElement (ei);
    
    switch (ngel.GetType())
      {
      case ET_TRIG:
        {
          auto trig = new (alloc) MyHighOrderTrig(order);
          // forward global vertex numbers to finite element,
          // used for orientation of edges:
          trig->SetVertexNumbers (ngel.vertices); 
          return *trig;
        }
      case ET_QUAD:
        {
          auto quad = new (alloc) MyHighOrderQuad(order);
          // forward global vertex numbers to finite element,
          // used for orientation of edges:
          quad->SetVertexNumbers (ngel.vertices);
          return *quad;
        }
      case ET_SEGM:
        {
          auto segm = new (alloc) MyHighOrderSegm(order);
          segm->SetVertexNumbers (ngel.vertices);
          return *segm;
        }
      default:
        throw Exception (string("Element type ")+ToString(ngel.GetType())+" not supported");
      }
  }
  
}
