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
  auto std__atanh = [](auto x){return std::atanh(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__atanh) , xp, std__atanh , arg0);
  run<EVE_VALUE>(EVE_NAME(atanh) , xp, eve::atanh , arg0);
  run<EVE_TYPE> (EVE_NAME(atanh) , xp, eve::atanh , arg0);
}
