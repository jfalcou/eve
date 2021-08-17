//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/count_true.hpp>

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
