//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  using L_VALUE = eve::logical<EVE_VALUE>;
  using L_TYPE = eve::logical<EVE_TYPE>;

  auto arg0 = eve::bench::bernoulli_<EVE_VALUE>();
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto eve__mul =  [](auto x,  auto y,  auto z){ return eve::mul[x](y, z); };

  eve::bench::experiment xp;
  run<eve::bench::types<L_VALUE, EVE_VALUE, EVE_VALUE>>(EVE_NAME( eve_mul) , xp, eve__mul, arg0, arg1, arg2);
  run<eve::bench::types<L_TYPE, EVE_TYPE, EVE_TYPE>> (EVE_NAME( eve_mul) , xp, eve__mul, arg0, arg1, arg2);
}
