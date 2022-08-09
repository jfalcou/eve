//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__oneminus = [](EVE_VALUE x, EVE_VALUE y) { return x ? EVE_VALUE(1-y):y; };
  auto eve__oneminus =  [](auto x,  auto y){ return eve::oneminus[x](y); };


  auto arg0 = eve::bench::random_<EVE_VALUE>(0, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__oneminus) , xp, std__oneminus, arg0, arg1);
  run<EVE_VALUE> (EVE_NAME(eve__oneminus) , xp, eve__oneminus, arg0, arg1);
  run<EVE_TYPE>  (EVE_NAME(eve__oneminus) , xp, eve__oneminus, arg0, arg1);
}
