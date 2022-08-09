//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::minlog(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::maxlog(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__coth = [](auto x){return std::tanh(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__coth) , xp, std__coth , arg0);
  run<EVE_VALUE>(EVE_NAME(coth) , xp, eve::coth , arg0);
  run<EVE_TYPE> (EVE_NAME(coth) , xp, eve::coth , arg0);

}
