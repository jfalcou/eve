//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__nearest = [](EVE_VALUE x) { return std::round(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__nearest) , xp, std__nearest, arg0);
  run<EVE_VALUE> (EVE_NAME(nearest) , xp, eve::nearest, arg0);
  run<EVE_TYPE>  (EVE_NAME(nearest) , xp, eve::nearest, arg0);
}
