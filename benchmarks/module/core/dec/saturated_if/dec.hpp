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
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;
  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto eve__dec =  [](auto x,  auto y){ return eve::dec[x][eve::saturated2](y); };
  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE>> (EVE_NAME(eve__dec) , xp, eve__dec, arg0, arg1);
  run<eve::bench::types<L_TYPE, EVE_TYPE>>  (EVE_NAME(eve__dec) , xp, eve__dec, arg0, arg1);


}
