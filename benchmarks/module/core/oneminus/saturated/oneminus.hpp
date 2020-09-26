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
