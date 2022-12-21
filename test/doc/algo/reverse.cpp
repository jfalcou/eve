#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int> v = {1,2,3,4,5,6,7,8,9,10,11,12,13};

  std::cout << " -> v                       = ";
  doc_utils::print(v);

  std::cout << " -> eve::algo::reverse(v)  = ";
  eve::algo::reverse(v);
  doc_utils::print(v);

  return 0;
}
