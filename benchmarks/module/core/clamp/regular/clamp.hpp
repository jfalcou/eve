//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <algorithm>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,EVE_VALUE(lmax/4));
  auto arg2 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(lmax/4),EVE_VALUE(lmax/2));

  auto std__clamp =  [](EVE_VALUE x,  EVE_VALUE y,  EVE_VALUE z){return std::clamp(x, y, z); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__clamp) , xp, std__clamp, arg0, arg1, arg2);
  run<EVE_VALUE>(EVE_NAME(clamp) , xp, eve::clamp, arg0, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(clamp) , xp, eve::clamp, arg0, arg1, arg2);
}
