//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, 3.5f};
  wide_ft qf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                        = " << pf << '\n'
    << "<- qf                        = " << qf << '\n'
    << "-> diff(powm1)(pf, qf) = " << eve::diff(eve::powm1)(pf, qf) << '\n';

  float xf = 3.0f;
  float yf = 2.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                        = " << xf << '\n'
    << "<- yf                        = " << yf << '\n'
    << "-> diff(powm1)(xf, yf) = " << eve::diff(eve::powm1)(xf, yf) << '\n';
  return 0;
}
