//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/constant/pio_4.hpp>

int main()
{
  auto lmax = EVE_VALUE(45);
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(secd[eve::quarter_circle2]) , xp, eve::secd[eve::quarter_circle2] , arg0);
  run<EVE_TYPE> (EVE_NAME(secd[eve::quarter_circle2]) , xp, eve::secd[eve::quarter_circle2] , arg0);
}
