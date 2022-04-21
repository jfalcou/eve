#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int>  v = {2,5,-9, 3,-8,2,-5,7,-2,3};
  std::vector<int>  w = {2,5,-9,-9,-8,2,-5,7,-2,3};

  std::cout << " -> v                       = ";
  doc_utils::print(v);

  std::cout << " -> w                       = ";
  doc_utils::print(w);

  auto [vv, ww] = eve::algo::mismatch(v, w);
  std::cout << " <- auto [vv, ww] = eve::algo::mismatch(v, ww);\n";
  std::cout << " -> mismatch at " << eve::read(vv) << " != " << eve::read(ww) << std::endl;
}
