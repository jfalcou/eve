#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(5);
  eve::algo::iota(r1, 0.5f);
  auto vr = eve::views::iota(0.5f, 5);

  std::cout << " <- std::vector<float> r1(5);\n";
  std::cout << " <- eve::algo::iota(r1, 0.5f);\n";

  std::cout << " -> r1                         = "; eve::detail::print(r1);
  std::cout << " -> vr                         = "; eve::detail::print(vr);

  auto vr0 = eve::views::iota(0.0f, 0);
  std::cout << " -> vr0                         = "; eve::detail::print(vr0);
  auto vr1 = eve::views::iota(0.0f, 1);
  std::cout << " -> vr1                         = "; eve::detail::print(vr1);

  return 0;
}
