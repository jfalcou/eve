//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/trunc.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__trunc = [](EVE_VALUE x) { return std::trunc(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__trunc) , xp, std__trunc, arg0);
  run<EVE_VALUE> (EVE_NAME(trunc) , xp, eve::trunc, arg0);
  run<EVE_TYPE>  (EVE_NAME(trunc) , xp, eve::trunc, arg0);
}
