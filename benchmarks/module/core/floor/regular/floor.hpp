//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__floor = [](EVE_VALUE x) { return std::floor(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__floor) , xp, std__floor, arg0);
  run<EVE_VALUE> (EVE_NAME(floor) , xp, eve::floor, arg0);
  run<EVE_TYPE>  (EVE_NAME(floor) , xp, eve::floor, arg0);
}
