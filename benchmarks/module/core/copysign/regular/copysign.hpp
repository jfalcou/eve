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

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__copysign =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(std::copysign(x, y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__copysign) , xp, std__copysign, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(copysign) , xp, eve::copysign, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(copysign) , xp, eve::copysign, arg0, arg1);
}
