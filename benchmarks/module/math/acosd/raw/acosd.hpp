//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosd.hpp>
#include <eve/function/radindeg.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acosd = [](auto x){return eve::radindeg( std::acos(x));};


  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acosd) , xp, std__acosd , arg0);
  run<EVE_VALUE>(EVE_NAME(raw_(eve::acosd)) , xp, eve::raw_(eve::acosd) , arg0);
  run<EVE_TYPE> (EVE_NAME(raw_(eve::acosd)) , xp, eve::raw_(eve::acosd) , arg0);

}
