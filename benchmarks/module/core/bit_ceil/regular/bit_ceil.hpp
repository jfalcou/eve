//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/bit_ceil.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__bit_ceil = [](EVE_VALUE x) { return x > 0 ? x : EVE_VALUE(-x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__bit_ceil) , xp, std__bit_ceil, arg0);
  run<EVE_VALUE> (EVE_NAME(bit_ceil) , xp, eve::bit_ceil, arg0);
  run<EVE_TYPE>  (EVE_NAME(bit_ceil) , xp, eve::bit_ceil, arg0);
}
