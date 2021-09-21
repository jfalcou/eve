//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sqr_abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__sqr_abs = [](EVE_VALUE x) { return EVE_VALUE(x*x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__sqr_abs) , xp, std__sqr_abs, arg0);
  run<EVE_VALUE> (EVE_NAME(sqr_abs) , xp, eve::sqr_abs, arg0);
  run<EVE_TYPE>  (EVE_NAME(sqr_abs) , xp, eve::sqr_abs, arg0);
}
