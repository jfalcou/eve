//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1);
//  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::maxflint(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__log1p = [](auto x){return std::log1p(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__log1p) , xp, std__log1p , arg0);
  run<EVE_VALUE>(EVE_NAME(log1p) , xp, eve::log1p , arg0);
  run<EVE_TYPE> (EVE_NAME(log1p) , xp, eve::log1p , arg0);

}
