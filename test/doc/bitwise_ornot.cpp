#include <eve/function/bitwise.hpp>
#include <eve/constant/nan.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main() {
  wide_it pi = {3, 5, 0, 127};
  wide_it qi = {4, 1, 0, 1023};
  std::cout << "---- simd" << '\n'
            << " <- pi =                        " << pi << '\n'
            << " <- qi =                        " << qi << '\n'
            << " -> eve::bitwise_ornot(pi, qi) = " << eve::bitwise_ornot(pi, qi)
            << '\n';

  std::uint32_t xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi =                           " << xi << '\n'
            << " yi =                           " << yi << '\n'
            << " -> eve::bitwise_ornot(xi, yi) = " << eve::bitwise_ornot(xi, yi)
            << '\n';
  return 0;
}
