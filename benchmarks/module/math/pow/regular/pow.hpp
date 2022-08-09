//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

int main()
{
  auto lmin = EVE_VALUE(-1.0);
  auto lmax = EVE_VALUE(100.0);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__pow = [](auto x, auto y){return std::pow(x, y);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__pow) , xp, std__pow , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(eve::pow) , xp, eve::pow , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(eve::pow) , xp, eve::pow , arg0, arg1);

}
