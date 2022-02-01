//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_eqz.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_eqz = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  { return !x; };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_eqz) , xp, std__is_eqz, arg0);
  run<EVE_VALUE> (EVE_NAME(is_eqz) , xp, eve::is_eqz, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_eqz) , xp, eve::is_eqz, arg0);
}
