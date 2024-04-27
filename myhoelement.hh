#ifndef FILE_MYHOELEMENT_HPP
#define FILE_MYHOELEMENT_HPP

#include <fem.hpp>

/*
  
It is also simple to implement high order elements ...

*/


namespace ngfem
{


  /*
    A Segment finite element with arbitrary order hierarchic basis
    functions
   */
  class MyHighOrderSegm : public ScalarFiniteElement<1> 
  {
    size_t vnums[2]; // global vertex numbers
  public:
    MyHighOrderSegm (int order);
    virtual ELEMENT_TYPE ElementType() const { return ET_SEGM; }

    template <typename T>
    void SetVertexNumbers (const T & avnums)
    {
      vnums[0] = avnums[0];
      vnums[1] = avnums[1];
    }
    
    virtual void CalcShape (const IntegrationPoint & ip, 
                            BareSliceVector<> shape) const;
  
    virtual void CalcDShape (const IntegrationPoint & ip, 
                             BareSliceMatrix<> dshape) const;

  private:
    template <class T>
    void T_CalcShape (const T& x, BareSliceVector<T> shape) const;
  };


  /*
    A triangular finite element with arbitrary order hierarchic basis
    functions
   */
  class MyHighOrderTrig : public ScalarFiniteElement<2>
  {
    size_t vnums[3]; // global vertex numbers   
  public:
    MyHighOrderTrig (int order);
    virtual ELEMENT_TYPE ElementType() const { return ET_TRIG; }

    template <typename T>
    void SetVertexNumbers (const T & avnums)
    {
      vnums[0] = avnums[0];
      vnums[1] = avnums[1];
      vnums[2] = avnums[2];
    }

    virtual void CalcShape (const IntegrationPoint & ip, 
                            BareSliceVector<> shape) const;
  
    virtual void CalcDShape (const IntegrationPoint & ip, 
                             BareSliceMatrix<> dshape) const;

  private:
    template <class T>
    void T_CalcShape (const T & x, const T & y, BareSliceVector<T> shape) const;
  };
    
    class MyHighOrderQuad : public ScalarFiniteElement<3>
  {
    size_t vnums[4]; // global vertex numbers   
  public:
    MyHighOrderQuad (int order);
    virtual ELEMENT_TYPE ElementType() const { return ET_QUAD; }

    template <typename T>
    void SetVertexNumbers (const T & avnums)
    {
      vnums[0] = avnums[0];
      vnums[1] = avnums[1];
      vnums[2] = avnums[2];
      vnums[3] = avnums[3];
    }

    virtual void CalcShape (const IntegrationPoint & ip, 
                            BareSliceVector<> shape) const;
  
    virtual void CalcDShape (const IntegrationPoint & ip, 
                             BareSliceMatrix<> dshape) const;

  private:
    template <class T>
    void T_CalcShape (const T & x, const T & y, BareSliceVector<T> shape) const;
  };
    
}

#endif

