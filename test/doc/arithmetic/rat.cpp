//==================================================================================================
#include <eve/module/core.hpp>
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
//#include <eve/function/rat.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<8>>;

int main()
{
  using eve::as;
  wide_ft pf = {1.25, 1.5, -3.123,  456.0
                , eve::pi(as(0.0)), eve::inf(as(0.0)), eve::minf(as(0.0)), eve::nan(as(0.0))};
  auto [n, d] = eve::rat(pf);
  std::cout << "---- simd" << '\n'
            << "<- pf                  = " << pf << '\n'
            << "-> n                   = " << n  << '\n'
            << "-> d                   = " << d  << '\n' ;


  double        xf = -3.0/5.0;
  auto [xn, xd] = eve::rat(xf);

  std::cout << "---- scalar" << '\n'
            << "<- xf                  = " << xf << '\n'
            << "-> xn                  = " << xn << '\n'
            << "-> xd                  = " << xd << '\n' ;
            ;
  return 0;
}
