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

  auto const std__oneminus = [](EVE_VALUE x, EVE_VALUE y) { return x ? EVE_VALUE(1-y):y; };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__oneminus) , xp, std__oneminus, arg0, arg1);
  run<EVE_VALUE> (EVE_NAME(saturated_(eve::oneminus)) , xp, eve::saturated_(eve::oneminus), arg0, arg1);
  run<EVE_TYPE>  (EVE_NAME(saturated_(eve::oneminus)) , xp, eve::saturated_(eve::oneminus), arg0, arg1);
}
