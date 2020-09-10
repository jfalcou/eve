//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinh.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-eve::oneotwoeps(eve::as<EVE_VALUE>())); //eve::Valmin<EVE_VALUE>());
  auto lmax = EVE_VALUE(eve::oneotwoeps(eve::as<EVE_VALUE>())); //eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asinh = [](auto x){return std::asinh(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asinh) , xp, std__asinh , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asinh) , xp, eve::asinh , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asinh) , xp, eve::asinh , arg0);
}
