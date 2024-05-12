//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/math/constant/oneotwoeps.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = [](){
    if constexpr(eve::floating_value<EVE_VALUE>) return eve::oneotwoeps(eve::as<EVE_VALUE>());
    else return eve::valmax(eve::as<EVE_VALUE>());
  }();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(1),lmax);

  auto std__div =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(x+y); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__div) , xp, std__div, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(div) , xp, eve::div, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(div) , xp, eve::div, arg0, arg1);
}
