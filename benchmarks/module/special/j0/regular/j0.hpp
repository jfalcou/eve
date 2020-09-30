//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/j0.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0.0);
  auto lmax = EVE_VALUE(20.0);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std_j0 =  [](auto x){return std::cyl_bessel_j(EVE_VALUE(0), x); };
  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_j0) , xp, std_j0 , arg0);
  run<EVE_VALUE>(EVE_NAME(j0) , xp, eve::j0 , arg0);
  run<EVE_TYPE> (EVE_NAME(j0) , xp, eve::j0 , arg0);

}
