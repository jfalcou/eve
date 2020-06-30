//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log1p.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__log1p = [](auto x){return std::log1p(x);};

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__log1p) , xp, std__log1p , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::log1p) , xp, eve::log1p , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::log1p) , xp, eve::log1p , arg0);

}
