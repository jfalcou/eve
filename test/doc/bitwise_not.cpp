#include <eve/function/bitwise.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main() {
  wide_it pi = {1, 2, ~0, 1023};

  std::cout << "---- simd" << '\n'
            << "<- pi =                  " << pi << '\n'
            << "-> eve::bitwise_not(pi) = " << eve::bitwise_not(pi) << '\n';

  std::uint32_t xi = 2;

  std::cout << "---- scalar" << '\n'
            << "<- xi =                  " << xi << '\n'
            << "-> eve::bitwise_not(xi) = " << eve::bitwise_not(xi) << '\n';
  return 0;
}
