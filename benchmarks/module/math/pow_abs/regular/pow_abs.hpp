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
#include <cmath>

int main(int argc, char** argv)
{
  auto const eve_pow_abs = [](auto x, auto y) { return eve::pow_abs(x, y); };
  auto const std_pow_abs = [](auto x, auto y) { return std::pow(std::abs(x), y); };
  auto lmin = EVE_VALUE(-10);
  auto lmax = EVE_VALUE(10);
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_pow_abs) , xp, std_pow_abs , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(pow_abs) , xp, eve_pow_abs , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pow_abs) , xp, eve_pow_abs , arg0, arg1);
}
