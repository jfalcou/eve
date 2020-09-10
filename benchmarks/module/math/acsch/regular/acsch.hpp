//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acsch.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <cmath>

int main()
{
//   auto lmin = EVE_VALUE(eve::Valmin<EVE_VALUE>());
//   auto lmax = EVE_VALUE(eve::Valmax<EVE_VALUE>());
  auto lmin = EVE_VALUE(-eve::oneotwoeps(eve::as<EVE_VALUE>())); //EVE_VALUE(eve::Valmin<EVE_VALUE>());
  auto lmax = EVE_VALUE(eve::oneotwoeps(eve::as<EVE_VALUE>()));  // EVE_VALUE(eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acsch = [](auto x){return std::asinh(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acsch) , xp, std__acsch , arg0);
  run<EVE_VALUE>(EVE_NAME(acsch) , xp, eve::acsch , arg0);
  run<EVE_TYPE> (EVE_NAME(acsch) , xp, eve::acsch , arg0);
}
