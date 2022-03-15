//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
  run<EVE_VALUE>(EVE_NAME(quarter_circle(eve::cospi)) , xp, eve::quarter_circle(eve::cospi) , arg0);
  run<EVE_TYPE> (EVE_NAME(quarter_circle(eve::cospi)) , xp, eve::quarter_circle(eve::cospi) , arg0);
}
