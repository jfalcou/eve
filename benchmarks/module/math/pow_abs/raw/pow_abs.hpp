//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
  auto const eve_rpow_abs = [](auto x, auto y) { return eve::raw(eve::pow_abs)(x, y); };
  auto const std_rpow_abs = [](auto x, auto y) { return std::exp(std::log(std::abs(x))*y); };
  auto lmin = EVE_VALUE(-10);
  auto lmax = EVE_VALUE(10);
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_rawpow_abs) , xp, std_rpow_abs , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(raw(pow_abs)) , xp, eve_rpow_abs , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(raw(pow_abs)) , xp, eve_rpow_abs , arg0, arg1);
}
