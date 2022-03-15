//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  using ui_t = eve::as_integer_t<EVE_VALUE, unsigned>;
  auto const std__popcount = [](EVE_VALUE x) { return std::popcount(eve::bit_cast(x, eve::as<ui_t>())); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__popcount) , xp, std__popcount, arg0);
  run<EVE_VALUE> (EVE_NAME(popcount) , xp, eve::popcount, arg0);
  run<EVE_TYPE>  (EVE_NAME(popcount) , xp, eve::popcount, arg0);
}
