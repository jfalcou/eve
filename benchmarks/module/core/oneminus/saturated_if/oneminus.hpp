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
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;

  auto const eve__oneminus = []<typename C,  typename T>( C x, T y) { return eve::saturated(eve::oneminus[x])(y);};

  auto arg0 = eve::bench::bernoulli_<EVE_VALUE>();
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE>>(EVE_NAME(eve::saturated(eve::oneminus)) , xp, eve__oneminus, arg0, arg1);
  run<eve::bench::types<L_TYPE, EVE_TYPE>> (EVE_NAME(eve::saturated(eve::oneminus)) , xp, eve__oneminus, arg0, arg1);
}
