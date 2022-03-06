#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(5);
  eve::algo::fill(r1, 8.0);
  std::cout << " <- std::vector<float> r1(5);\n";
  std::cout << " <- eve::algo::fill(r1, 8.0);\n";
  std::cout << " -> r1                         = "; eve::detail::print(r1);
  return 0;
}
