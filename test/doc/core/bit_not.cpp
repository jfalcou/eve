#include <eve/function/bit.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {1, 2, ~0, 1023};

  std::cout << "---- simd" << '\n'
            << "<- pi =                  " << pi << '\n'
            << "-> eve::bit_not(pi) = " << eve::bit_not(pi) << '\n';

  std::uint32_t xi = 2;

  std::cout << "---- scalar" << '\n'
            << "<- xi =                  " << xi << '\n'
            << "-> eve::bit_not(xi) = " << eve::bit_not(xi) << '\n';
  return 0;
}
