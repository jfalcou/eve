//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
#include <eve/module/math.hpp>
#include <iostream>


using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> diff(acosd)(pf) = " << eve::diff(eve::acosd)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(acosd)(xf) = " << eve::diff(eve::acosd)(xf) << '\n'; 
  return 0;
}
