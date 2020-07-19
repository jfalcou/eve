//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;
  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto eve__inc =  [](auto x,  auto y){ return eve::saturated_(eve::inc[x])(y); };
  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE>> (EVE_NAME(eve__inc) , xp, eve__inc, arg0, arg1);
  run<eve::bench::types<L_TYPE, EVE_TYPE>>  (EVE_NAME(eve__inc) , xp, eve__inc, arg0, arg1);


}
