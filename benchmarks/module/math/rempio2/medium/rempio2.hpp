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
  auto lmax = eve::Rempio2_limit[eve::medium2](eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin, lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(rempio2[eve::medium2])   , xp, eve::rempio2[eve::medium2], arg0);
  run<EVE_TYPE >(EVE_NAME(rempio2[eve::medium2])   , xp, eve::rempio2[eve::medium2], arg0);
  run<EVE_VALUE>(EVE_NAME(rempio2)                 , xp, eve::rempio2              , arg0);
  run<EVE_TYPE >(EVE_NAME(rempio2)                 , xp, eve::rempio2              , arg0);
}
