//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__oneminus = [](EVE_VALUE x) { return EVE_VALUE(1-x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__oneminus) , xp, std__oneminus, arg0);
  run<EVE_VALUE> (EVE_NAME(oneminus) , xp, eve::oneminus, arg0);
  run<EVE_TYPE>  (EVE_NAME(oneminus) , xp, eve::oneminus, arg0);
}
