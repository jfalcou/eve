//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/clamp.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <algorithm>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,EVE_VALUE(lmax/4));
  auto arg2 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(lmax/4),EVE_VALUE(lmax/2));

  auto std__clamp =  [](EVE_VALUE x,  EVE_VALUE y,  EVE_VALUE z){return std::clamp(x, y, z); };

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__clamp) , xp, std__clamp, arg0, arg1, arg2);
  run<EVE_VALUE>(EVE_NAME(eve::clamp) , xp, eve::clamp, arg0, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(eve::clamp) , xp, eve::clamp, arg0, arg1, arg2);
}
