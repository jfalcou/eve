//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log2.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__log2 = [](auto x){return std::log2(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__log2) , xp, std__log2 , arg0);
  run<EVE_VALUE>(EVE_NAME(log2) , xp, eve::log2 , arg0);
  run<EVE_TYPE> (EVE_NAME(log2) , xp, eve::log2 , arg0);

}
