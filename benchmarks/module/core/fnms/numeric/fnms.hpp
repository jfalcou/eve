//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnms.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__fnms =  [](EVE_VALUE x,  EVE_VALUE y, auto z){return EVE_VALUE(-std::fma(x, y, z)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__fnms) , xp, std__fnms, arg0, arg1, arg2);
  run<EVE_VALUE>(EVE_NAME(numeric_(eve::fnms)) , xp, eve::numeric_(eve::fnms), arg0, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(numeric_(eve::fnms)) , xp, eve::numeric_(eve::fnms), arg0, arg1, arg2);
}
