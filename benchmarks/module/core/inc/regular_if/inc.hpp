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
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;
  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto eve__inc =  [](auto x,  auto y){ return eve::inc[x](y); };


  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE>> (EVE_NAME(eve__inc) , xp, eve__inc, arg0, arg1);
  run<eve::bench::types<L_TYPE, EVE_TYPE>>  (EVE_NAME(eve__inc) , xp, eve__inc, arg0, arg1);

}
