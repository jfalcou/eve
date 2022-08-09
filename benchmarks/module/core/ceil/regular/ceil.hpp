//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__ceil = [](EVE_VALUE x) { return std::ceil(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__ceil) , xp, std__ceil, arg0);
  run<EVE_VALUE> (EVE_NAME(ceil) , xp, eve::ceil, arg0);
  run<EVE_TYPE>  (EVE_NAME(ceil) , xp, eve::ceil, arg0);
}
