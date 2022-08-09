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
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__log10 = [](auto x){return std::log(x)*EVE_VALUE(4.34294481903252e-01);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__log10) , xp, std__log10 , arg0);
  run<EVE_VALUE>(EVE_NAME(log10) , xp, eve::log10 , arg0);
  run<EVE_TYPE> (EVE_NAME(log10) , xp, eve::log10 , arg0);

}
