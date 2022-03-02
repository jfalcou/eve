//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asech = [](auto x){return std::acosh(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asech) , xp, std__asech , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asech) , xp, eve::asech , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asech) , xp, eve::asech , arg0);
}
