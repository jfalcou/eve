//================================================================================================== 
/** 
  EVE - Expressive Vector Engine 
  Copyright : EVE Contributors & Maintainers 
  SPDX-License-Identifier: MIT 
**/ 
//================================================================================================== 
 
#include <eve/module/arithmetic.hpp> 
#include <eve/module/math.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> diff(acotd)(pf) = " << eve::diff(eve::acotd)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(acotd)(xf) = " << eve::diff(eve::acotd)(xf) << '\n';
  return 0;
}
