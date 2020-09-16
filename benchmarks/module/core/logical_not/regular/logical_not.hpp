//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_not.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  auto const std__logical_not = [](auto x) { return EVE_VALUE(!x); };
  run<EVE_VALUE> (EVE_NAME(std__logical_not) , xp, std__logical_not, arg0);

  run<EVE_VALUE> (EVE_NAME(logical_not) , xp, eve::logical_not, arg0);
  run<EVE_TYPE>  (EVE_NAME(logical_not) , xp, eve::logical_not, arg0);
}
