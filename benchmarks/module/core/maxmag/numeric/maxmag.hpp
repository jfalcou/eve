//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/maxmag.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);


  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(numeric_(eve::maxmag)) , xp, eve::numeric_(eve::maxmag), arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(numeric_(eve::maxmag)) , xp, eve::numeric_(eve::maxmag), arg0, arg1);
}
