//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::Valmin<EVE_VALUE>());
  auto lmax = EVE_VALUE(eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__tan = [](auto x){return std::tan(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__tan) , xp, std__tan , arg0);
  run<EVE_VALUE>(EVE_NAME(big_(eve::tan)) , xp, eve::big_(eve::tan) , arg0);
  run<EVE_TYPE> (EVE_NAME(big_(eve::tan)) , xp, eve::big_(eve::tan) , arg0);

}
