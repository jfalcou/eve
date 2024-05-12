//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>

int main()
{
  EVE_VALUE lmax = eve::cardinal_v<EVE_VALUE>;
  EVE_VALUE lmin = -lmax;
  using L_TYPE = eve::logical<EVE_TYPE>;
  if (lmin > 0) lmin = 0;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg00= eve::bench::bernoulli_<EVE_VALUE>();

  eve::bench::experiment xp;
  run<L_TYPE>(EVE_NAME(count_true) , xp, eve::count_true, arg00);
  run<EVE_TYPE> (EVE_NAME(count_true) , xp, eve::count_true, arg0);
}
