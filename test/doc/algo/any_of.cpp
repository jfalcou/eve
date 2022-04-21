#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int>  v = {2,6,-10,32,-8,2,-6,8,-2,4};

  std::cout << " -> v                                  = ";
  doc_utils::print(v);

  std::cout << " -> eve::algo::any_of(v, i >= 4)       = "
            << std::boolalpha << eve::algo::any_of(v, [](auto i){ return i >= 4; })<< "\n";

  std::cout << " -> eve::algo::any_of(v, eve::is_odd)  = "
            << std::boolalpha << eve::algo::any_of(v, eve::is_odd)<< "\n";
  return 0;
}
