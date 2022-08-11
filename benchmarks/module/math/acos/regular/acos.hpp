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
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acos = [](auto x){return std::acos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acos) , xp, std__acos , arg0);
  run<EVE_VALUE>(EVE_NAME(acos) , xp, eve::acos , arg0);
  run<EVE_TYPE> (EVE_NAME(acos) , xp, eve::acos , arg0);
}
