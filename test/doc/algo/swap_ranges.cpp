#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(10), r2(10);
  eve::algo::copy(eve::views::iota_with_step(0.0f, 2.0f, 10),  r1);
  eve::algo::copy(eve::views::iota_with_step(0.0f, 1.0f, 10), r2);
  std::cout << " <- std::vector<float> r1(5), r2(10);\n";
  std::cout << " <- eve::algo::copy(eve::views::iota_with_step(0.0f, 2.0f, 5),  r1);\n";
  std::cout << " <- eve::algo::copy(eve::views::iota_with_step(0.0f, 1.0f, 10), r2);\n";
  std::cout << " -> r1                         = "; eve::detail::print(r1);
  std::cout << " -> r2                         = "; eve::detail::print(r2);
  eve::algo::swap_ranges(r1, r2);
  std::cout << " <- eve::algo::swap_ranges(r1, r2);\n";
  std::cout << " -> r1                         = "; eve::detail::print(r1);
  std::cout << " -> r2                         = "; eve::detail::print(r2);
  return 0;
}
