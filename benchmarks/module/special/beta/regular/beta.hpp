//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
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
