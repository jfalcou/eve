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

  auto const eve__oneminus = []<typename C,  typename T>( C x, T y) { return eve::saturated_(eve::oneminus[x])(y);};

  auto arg00 = eve::bench::random_<EVE_VALUE>(0, 1);
  auto arg0 = eve::bench::bernoulli_<EVE_VALUE>();
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE>>(EVE_NAME(eve::saturated_(eve::oneminus)) , xp, eve__oneminus, arg0, arg1);
  run<eve::bench::types<EVE_VALUE, EVE_TYPE >>(EVE_NAME(eve::saturated_(eve::oneminus)) , xp, eve__oneminus, arg00, arg1);
  run<eve::bench::types<L_TYPE, EVE_TYPE>> (EVE_NAME(eve::saturated_(eve::oneminus)) , xp, eve__oneminus, arg0, arg1);
}
