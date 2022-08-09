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

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(1),lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(saturated(eve::div)) , xp, eve::saturated(eve::div), arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(saturated(eve::div)) , xp, eve::saturated(eve::div), arg0, arg1);
}
