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
  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__log2 = [](auto x){return std::log2(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__log2) , xp, std__log2 , arg0);
  run<EVE_VALUE>(EVE_NAME(log2) , xp, eve::log2 , arg0);
  run<EVE_TYPE> (EVE_NAME(log2) , xp, eve::log2 , arg0);

}
