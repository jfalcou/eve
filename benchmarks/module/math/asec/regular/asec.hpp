//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asec.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(1);
  auto lmax = EVE_VALUE(eve::Oneotwoeps<EVE_VALUE>()); //eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asec = [](auto x){return std::acos(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asec) , xp, std__asec , arg0);
  run<EVE_VALUE>(EVE_NAME(asec) , xp, eve::asec , arg0);
  run<EVE_TYPE> (EVE_NAME(asec) , xp, eve::asec , arg0);
}
