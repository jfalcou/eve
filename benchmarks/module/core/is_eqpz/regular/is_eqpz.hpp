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

  auto const std__is_eqpz = [](EVE_VALUE e) -> eve::logical<EVE_VALUE>  {  return eve::is_positive(e) && eve::is_eqz(e); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_eqpz) , xp, std__is_eqpz, arg0);
  run<EVE_VALUE> (EVE_NAME(is_eqpz) , xp, eve::is_eqpz, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_eqpz) , xp, eve::is_eqpz, arg0);
}
