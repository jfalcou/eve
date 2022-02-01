//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/erfc.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-27);
  auto lmax = -lmin;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std_erfc =  [](auto x){return std::erfc(x); };
  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_erfc) , xp, std_erfc , arg0);
  run<EVE_VALUE>(EVE_NAME(erfc) , xp, eve::erfc , arg0);
  run<EVE_TYPE> (EVE_NAME(erfc) , xp, eve::erfc , arg0);

}
