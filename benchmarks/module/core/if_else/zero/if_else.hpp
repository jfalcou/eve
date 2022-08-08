//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__if_else =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(x ? y : EVE_VALUE(01)); };
  auto eve__if_else =  [](auto x,  auto y){return eve::if_else(x, y, eve::zero); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__if_else) , xp, std__if_else, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(eve__if_else) , xp, eve__if_else, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(eve__if_else) , xp, eve__if_else, arg0, arg1);
}
