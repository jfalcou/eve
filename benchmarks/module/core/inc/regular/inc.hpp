//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__inc = [](EVE_VALUE x) { return x > 0 ? x : EVE_VALUE(-x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__inc) , xp, std__inc, arg0);
  run<EVE_VALUE> (EVE_NAME(inc) , xp, eve::inc, arg0);
  run<EVE_TYPE>  (EVE_NAME(inc) , xp, eve::inc, arg0);
}
