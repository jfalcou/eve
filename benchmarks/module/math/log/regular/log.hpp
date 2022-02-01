//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/log.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__log = [](auto x){return std::log(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__log) , xp, std__log , arg0);
  run<EVE_VALUE>(EVE_NAME(log) , xp, eve::log , arg0);
  run<EVE_TYPE> (EVE_NAME(log) , xp, eve::log , arg0);

}
