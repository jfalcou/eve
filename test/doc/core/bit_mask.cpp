#include <eve/function/bit.hpp>
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
            << "-> eve::bit_mask(pi) = " << eve::bit_mask(pi) << '\n'
            << "<- pf =                  " << pf << '\n'
            << "-> eve::bit_mask(pf) = " << eve::bit_mask(pf) << '\n';

  std::uint32_t xi = 2;

  std::cout << "---- scalar" << '\n'
            << "<- xi =                  " << xi << '\n'
            << "-> eve::bit_mask(xi) = " << eve::bit_mask(xi) << '\n';
  return 0;
}
