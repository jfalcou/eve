#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int>  v = {2,5,-9,3,-8,2,-5,7,-2,3};
  std::vector<int>  w = {-9,3,-8,2,2,5,-5,7,-2,3};

  std::cout << " -> v                       = ";
  doc_utils::print(v);

  std::cout << " -> w                       = ";
  doc_utils::print(w);

  eve::algo::swap_ranges(v, w);
  std::cout << " <- eve::algo::swap_ranges(v, w);\n";

  std::cout << " -> v                       = ";
  doc_utils::print(v);

  std::cout << " -> w                       = ";
  doc_utils::print(w);

  return 0;
}
