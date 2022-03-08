#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(10), r2(10);
  eve::algo::iota(r1, 1.0f);
  std::cout << " -> r1                         = "; eve::detail::print(r1);
  auto res = eve::algo::remove_if(r1, eve::is_odd);
  r1.erase(res, r1.end());
  std::cout << " <- std::vector<float> r1(10);\n";
  std::cout << " <- eve::views::iota(r1, 1.0f);\n";
  std::cout << " <- auto res = eve::algo::remove_if(r1, eve::is_odd);\n";
  std::cout << " <- r1.erase(res, r1.end()); \n";
  std::cout << " -> r1 with removed odd        = "; eve::detail::print(r1);
  auto re1 = eve::algo::remove(r1, 6.0f);
  r1.erase(re1, r1.end());
  std::cout << " -> r1 with removed 6.0f       = "; eve::detail::print(r1);
  return 0;
}
