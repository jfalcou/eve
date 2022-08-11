//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>

#include <eve/module/special.hpp>
int main()
{
  auto lmin = EVE_VALUE(-1000);
  auto lmax = EVE_VALUE(1000);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(erfcx) , xp, eve::erfcx , arg0);
  run<EVE_TYPE> (EVE_NAME(erfcx) , xp, eve::erfcx , arg0);

}
