//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rem.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(1),lmax);

  auto std__rem =  [](EVE_VALUE x,  EVE_VALUE y) { return EVE_VALUE(x%y); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__rem) , xp, std__rem, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(rem) , xp, eve::rem, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(rem) , xp, eve::rem, arg0, arg1);
}
