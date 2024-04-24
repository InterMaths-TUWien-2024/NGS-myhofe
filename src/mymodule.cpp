#include <comp.hpp>
#include <python_comp.hpp>

#include "myhofespace.hpp"


PYBIND11_MODULE(myhofe, m)
{
  cout << "Loading myhofe library" << endl;

  ngcomp::ExportFESpace<ngcomp::MyHighOrderFESpace>(m, "MyHighOrderFESpace")
    ;
}
