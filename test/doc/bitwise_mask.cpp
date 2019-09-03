#include <eve/function/bitwise.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;
using wide_f  = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_it pi = {0, 2, ~0, 1023};
  wide_f  pf = {0.0f, -0.0f, 1.0f, -10.0f};

  std::cout << "---- simd" << '\n'
            << "<- pi =                  " << pi << '\n'
            << "-> eve::bitwise_mask(pi) = " << eve::bitwise_mask(pi) << '\n'
            << "<- pf =                  " << pf << '\n'
            << "-> eve::bitwise_mask(pf) = " << eve::bitwise_mask(pf) << '\n';

  std::uint32_t xi = 2;

  std::cout << "---- scalar" << '\n'
            << "<- xi =                  " << xi << '\n'
            << "-> eve::bitwise_mask(xi) = " << eve::bitwise_mask(xi) << '\n';
  return 0;
}
