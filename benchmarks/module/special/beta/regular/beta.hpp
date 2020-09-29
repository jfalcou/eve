//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/beta.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-10);
  auto lmax = EVE_VALUE(10);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__beta = [](auto x, auto y){return std::beta(x, y);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__beta) , xp, std__beta , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(beta) , xp, eve::beta , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(beta) , xp, eve::beta , arg0, arg1);

}
