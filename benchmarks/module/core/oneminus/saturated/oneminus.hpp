//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto std__oneminus = [](EVE_VALUE e) { return e <= eve::valmin(eve::as<EVE_VALUE>())+1 ? eve::valmax(eve::as<EVE_VALUE>()) : EVE_VALUE(1-e); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__oneminus) , xp, std__oneminus, arg0);
  run<EVE_VALUE> (EVE_NAME(eve::saturated(eve::oneminus)) , xp, eve::saturated(eve::oneminus), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve::saturated(eve::oneminus)) , xp, eve::saturated(eve::oneminus), arg0);
}
