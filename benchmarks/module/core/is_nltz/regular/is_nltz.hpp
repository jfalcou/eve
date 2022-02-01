//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/is_nltz.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_nltz = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  { return !(x <= 0); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_nltz) , xp, std__is_nltz, arg0);
  run<EVE_VALUE> (EVE_NAME(is_nltz) , xp, eve::is_nltz, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_nltz) , xp, eve::is_nltz, arg0);
}
