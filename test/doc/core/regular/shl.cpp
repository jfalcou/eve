#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<4>>;

int main()
{
  wide_it pi = {100, 200, -2, 3};
  wide_it qi = {1, 2, 3, 2};

  std::cout << "---- simd" << '\n'
            << "<- pi               = " << pi << '\n'
            << "<- qi               = " << qi << '\n'
            << "-> eve::shl(pi, qi) = " << eve::shl(pi, qi) << '\n';

  iT xi = 2, mxi = -2, yi = 3;

  std::cout << "---- scalar" << '\n'
            << "<- xi                = " << xi << '\n'
            << "<- mxi               = " << mxi << '\n'
            << "<- yi                = " << yi << '\n'
            << "-> eve::shl(xi, yi)  = " << eve::shl(xi, yi) << '\n'
            << "-> eve::shl(mxi, yi) = " << eve::shl(mxi, yi) << '\n';
  return 0;
}
