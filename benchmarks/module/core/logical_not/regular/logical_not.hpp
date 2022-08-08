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

  eve::bench::experiment xp;
  auto const std__logical_not = [](auto x) { return EVE_VALUE(!x); };
  run<EVE_VALUE> (EVE_NAME(std__logical_not) , xp, std__logical_not, arg0);

  run<EVE_VALUE> (EVE_NAME(logical_not) , xp, eve::logical_not, arg0);
  run<EVE_TYPE>  (EVE_NAME(logical_not) , xp, eve::logical_not, arg0);
}
