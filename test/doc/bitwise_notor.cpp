#include <eve/function/bitwise.hpp>
#include <eve/constant/nan.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main() {
  wide_it pi = {3, -2, 2, 1023};
  wide_it qi = {4, -1, 3, ~0};
  std::cout << "---- simd" << '\n'
            << " <- pi =                        " << pi << '\n'
            << " <- qi =                        " << qi << '\n'
            << " -> eve::bitwise_notor(pi, qi) = " << eve::bitwise_notor(pi, qi)
            << '\n';

  std::uint32_t xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi =                           " << xi << '\n'
            << " yi =                           " << yi << '\n'
            << " -> eve::bitwise_notor(xi, yi) = " << eve::bitwise_notor(xi, yi)
            << '\n';
  return 0;
}
