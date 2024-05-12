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

  auto const eve__saturate = [](auto x) { return eve::saturate(x, eve::as<std::int16_t>()); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(eve__saturate) , xp, eve__saturate, arg0);
  run<EVE_TYPE>  (EVE_NAME(eve__saturate) , xp, eve__saturate, arg0);
}
