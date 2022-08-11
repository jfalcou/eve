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

  auto const std__bit_floor = [](EVE_VALUE x) { return x > 0 ? x : EVE_VALUE(-x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__bit_floor) , xp, std__bit_floor, arg0);
  run<EVE_VALUE> (EVE_NAME(bit_floor) , xp, eve::bit_floor, arg0);
  run<EVE_TYPE>  (EVE_NAME(bit_floor) , xp, eve::bit_floor, arg0);
}
