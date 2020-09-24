//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-10000.0);
  auto lmax = EVE_VALUE(10000.0);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__pow_abs = [](auto x, auto y){return std::pow(std::abs(x), y);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__pow_abs) , xp, std__pow_abs , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(pedantic_(eve::pow_abs)) , xp, eve::pedantic_(eve::pow_abs) , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pedantic_(eve::pow_abs)) , xp, eve::pedantic_(eve::pow_abs) , arg0, arg1);

}
