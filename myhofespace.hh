#ifndef FILE_MYHOFESPACE_HPP
#define FILE_MYHOFESPACE_HPP

/*

  My own FESpace for high order finite elements ...

*/


namespace ngcomp
{
  
  class MyHighOrderFESpace : public FESpace
  {
    int order;
    
    // dofs on i-th edge: [first_edge_dof[i], first_edge_dof[i+1])
    Array<int> first_edge_dof;
    // same for faces:
    Array<int> first_face_dof;
  public:
    MyHighOrderFESpace (shared_ptr<MeshAccess> ama, const Flags & flags);

    string GetClassName () const override
    { return "MyHighOrderFESpace"; }

    void Update() override;

    void GetDofNrs (ElementId ei, Array<DofId> & dnums) const override;
    FiniteElement & GetFE (ElementId ei, Allocator & alloc) const override;
  };
}    

#endif
