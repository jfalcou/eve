#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(5), r2(5), r3(5);
//  eve::algo::iota_scaled(r1, 0.5f, 2.0f); // why this does not exists ?
  auto vr = eve::views::iota_scaled(0.5f, 2.0f, 5);
  eve::algo::copy(vr, r1);

  std::cout << " <- std::vector<float> r1(5), r2(5), r3(5);\n";
  std::cout << " <- eve::algo::iota_scaled(r1, 0.5f);\n";
  std::cout << " <- std::iota(r2.begin(), r2.end(), 0.5f);\n";
  std::cout << " <- eve::algo::copy(vr, r1); // vr is not suited for direct output\n";
  std::cout << " -> std::ranges::equal(r1, r2) = "<< std::boolalpha << std::ranges::equal(r1, r2) << '\n';
  std::cout << " -> eve::algo::equal(vr, r2)   = "<< std::boolalpha << eve::algo::equal(vr, r2) << '\n';
  std::cout << " -> vr                         = "; eve::detail::print(vr);
  std::cout << " -> r1                         = "; eve::detail::print(r1);
  return 0;
}
