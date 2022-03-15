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

  auto const std__is_not_finite = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  { return !std::isfinite(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_not_finite) , xp, std__is_not_finite, arg0);
  run<EVE_VALUE> (EVE_NAME(is_not_finite) , xp, eve::is_not_finite, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_not_finite) , xp, eve::is_not_finite, arg0);
}
