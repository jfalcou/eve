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
  auto const eve_rpow = [](auto x, auto y) { return eve::raw_(eve::pow)(x, y); };
  auto const std_rpow = [](auto x, auto y) { return std::exp(std::log(x)*y); };
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(10);
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_pow) , xp, std_rpow , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(raw_(pow)) , xp, eve_rpow , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(raw_(pow)) , xp, eve_rpow , arg0, arg1);
}
