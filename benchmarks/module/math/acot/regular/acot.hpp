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
  auto lmin = EVE_VALUE(-5);
  auto lmax = EVE_VALUE(5);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acot = [](auto x){return std::atan(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acot) , xp, std__acot , arg0);
  run<EVE_VALUE>(EVE_NAME(acot) , xp, eve::acot , arg0);
  run<EVE_TYPE> (EVE_NAME(acot) , xp, eve::acot , arg0);
}
