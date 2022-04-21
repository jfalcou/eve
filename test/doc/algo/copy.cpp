#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<double>  v = {2.5,6.8,-10.62,3.2,-8.8,2.7,-6.66,8.5,-2.01,4.8};
  std::vector<double>  w(v.size());

  std::cout << " -> v                       = ";
  doc_utils::print(v);

  eve::algo::copy(v, w);
  std::cout << " -> eve::algo::copy(v, w);  = ";
  doc_utils::print(w);

  return 0;
}
