//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__manhattan =  [](EVE_VALUE x, EVE_VALUE y){return EVE_VALUE(std::abs(x)+std::abs(y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__manhattan) , xp, std__manhattan, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(manhattan) , xp, eve::manhattan, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(manhattan) , xp, eve::manhattan, arg0, arg1);
}
