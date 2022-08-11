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

  auto const std__round = [](EVE_VALUE x) { return std::round(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__round) , xp, std__round, arg0);
  run<EVE_VALUE> (EVE_NAME(round) , xp, eve::round, arg0);
  run<EVE_TYPE>  (EVE_NAME(round) , xp, eve::round, arg0);
}
