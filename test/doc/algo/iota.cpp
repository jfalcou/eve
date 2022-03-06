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
  return 0;
}
