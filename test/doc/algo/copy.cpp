#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(5);
  auto vr1 = eve::views::iota_scaled(0.5f, 2.0f, 5);
  eve::algo::copy(vr1, r1);
  std::cout << " <- std::vector<float> r1(5);\n";
  std::cout << " <- auto vr1 = eve::views::iota_scaled(0.5f, 2.0f, 5);\n";
  std::cout << " <- eve::algo::copy(vr1, r1);\n";
  std::cout << " -> eve::algo::equal(r1, vr1)  = "<< std::boolalpha << eve::algo::equal(r1, vr1)<< '\n';

  std::cout << " -> r1                         = "; eve::detail::print(r1);
  return 0;
}
