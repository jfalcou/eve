//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_real = [](EVE_VALUE ) { return true; };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_real) , xp, std__is_real, arg0);
  run<EVE_VALUE> (EVE_NAME(is_real) , xp, eve::is_real, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_real) , xp, eve::is_real, arg0);
}
