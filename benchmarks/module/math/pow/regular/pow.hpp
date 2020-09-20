//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const eve_pow = [](auto x, auto y) { return eve::pow(x, y); };
  auto const std_pow = [](auto x, auto y) { return std::pow(x, y); };
  auto lmin = EVE_VALUE(1);
  auto lmax = EVE_VALUE(10);
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_pow) , xp, std_pow , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(pow) , xp, eve_pow , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pow) , xp, eve_pow , arg0, arg1);
}
