//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
  auto lmax = EVE_VALUE(90);
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(tand[eve::half_circle]) , xp, eve::tand[eve::half_circle] , arg0);
  run<EVE_TYPE> (EVE_NAME(tand[eve::half_circle]) , xp, eve::tand[eve::half_circle] , arg0);

}
