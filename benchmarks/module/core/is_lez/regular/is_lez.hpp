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

  auto const std__is_lez = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  { return x <= 0; };
  auto const is_lez1 = []<typename T>(T x) { return eve::is_lez[x < T(-4)](x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_lez) , xp, std__is_lez, arg0);
  run<EVE_VALUE> (EVE_NAME(is_lez) , xp, eve::is_lez, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_lez) , xp, eve::is_lez, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_lez1) , xp, is_lez1, arg0);
}
