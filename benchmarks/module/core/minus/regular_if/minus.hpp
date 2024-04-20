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

  auto const std__minus = [](EVE_VALUE x, EVE_VALUE y) { return x > 0? EVE_VALUE(-y):y; };
  auto eve__minus =  [](auto x,  auto y){ return eve::minus[x > 0](y); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(-1, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__minus) , xp, std__minus, arg0, arg1);
  run<EVE_VALUE> (EVE_NAME(eve_minus) , xp, eve__minus, arg0, arg1);
  run<EVE_TYPE>  (EVE_NAME(eve_minus) , xp, eve__minus, arg0, arg1);
}
