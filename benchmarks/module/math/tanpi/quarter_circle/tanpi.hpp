//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

int main()
{
  auto lmax = EVE_VALUE(0.25);
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(tanpi[eve::quarter_circle2]) , xp, eve::tanpi[eve::quarter_circle2] , arg0);
  run<EVE_TYPE> (EVE_NAME(tanpi[eve::quarter_circle2]) , xp, eve::tanpi[eve::quarter_circle2] , arg0);
}
