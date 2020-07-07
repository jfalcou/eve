//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;

  auto const eve__oneminus = [](  L_VALUE x, EVE_VALUE y) { return eve::saturated_(eve::oneminus[x])(y);};
  auto const eve__oneminus1= [](  L_TYPE  x, EVE_TYPE  y) -> EVE_TYPE { return eve::saturated_(eve::oneminus[x])(y);};
  auto arg0 = eve::bench::bernoulli_<EVE_VALUE>();
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE>>(EVE_NAME(eve::saturated_(eve::oneminus)) , xp, eve__oneminus, arg0, arg1);
//  run<eve::bench::types<L_VALUE, EVE_TYPE >>(EVE_NAME(eve::saturated_(eve::oneminus)) , xp, eve__oneminus, arg0, arg1);
  run<eve::bench::types<L_TYPE, EVE_TYPE>> (EVE_NAME(eve::saturated_(eve::oneminus)) , xp, eve__oneminus1, arg0, arg1);
}
