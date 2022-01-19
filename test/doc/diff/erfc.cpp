//================================================================================================== 
/** 
  EVE - Expressive Vector Engine 
  Copyright : EVE Contributors & Maintainers 
  SPDX-License-Identifier: MIT 
**/ 
//================================================================================================== 
 
#include <eve/module/arithmetic.hpp> 
#include <eve/module/special.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft pf = { 0.0f, 1.0f, -1.0f, -0.5f};

  std::cout
    << "---- simd" << '\n'
    << "<- pf                   = " << pf << '\n'
    << "-> diff(erfc)(pf) = " << eve::diff(eve::erfc)(pf) << '\n';

  float xf = 1.0f;

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                   = " << xf << '\n'
    << "-> diff(erfc)(xf) = " << eve::diff(eve::erfc)(xf) << '\n'; 
  return 0;
}
