//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/constant/maxlog2.hpp>
#include <eve/module/math/constant/minlog2.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::minlog2(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::maxlog2(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__exp2 = [](auto x){return std::exp2(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__exp2) , xp, std__exp2 , arg0);
  run<EVE_VALUE>(EVE_NAME(exp2) , xp, eve::exp2 , arg0);
  run<EVE_TYPE> (EVE_NAME(exp2) , xp, eve::exp2 , arg0);

}
