//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
//   auto lmin = EVE_VALUE(-1.0);
//   auto lmax = EVE_VALUE(100.0);

  auto const eve_rpow = [](auto x, auto y) { return eve::raw(eve::pow)(x, y); };
  auto const std_rpow = [](auto x, auto y) { return std::exp(std::log(x)*y); };
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(10);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  eve::bench::experiment xp;

  run<EVE_VALUE>(EVE_NAME(std_pow) , xp, std_rpow , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(raw(pow)) , xp, eve_rpow , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(raw(pow)) , xp, eve_rpow , arg0, arg1);
}
