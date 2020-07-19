//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/all.hpp>

int main()
{
  EVE_VALUE lmax = eve::cardinal_v<EVE_VALUE>;
  EVE_VALUE lmin = -lmax;
  using L_TYPE = eve::logical<EVE_TYPE>;
  if (lmin > 0) lmin = 0;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg00= eve::bench::bernoulli_<EVE_VALUE>();

  eve::bench::experiment xp;
  run<L_TYPE>(EVE_NAME(all) , xp, eve::all, arg00);
  run<EVE_TYPE> (EVE_NAME(all) , xp, eve::all, arg0);
}
