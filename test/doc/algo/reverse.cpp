#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int> v= {1,2,3,4,5,6,7,8,9,10,11,12,13};

  std::cout << " -> v                       = ";
  doc_utils::print(v);

  std::cout << " -> eve::views::reverse(v)  = ";
  doc_utils::print(eve::views::reverse(v));

  return 0;
}
