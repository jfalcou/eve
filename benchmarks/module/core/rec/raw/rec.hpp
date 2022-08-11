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
  auto lmax = [](){
    if constexpr(eve::floating_value<EVE_VALUE>) return eve::oneotwoeps(eve::as<EVE_VALUE>());
    else return eve::valmax(eve::as<EVE_VALUE>());
  }();
  auto lmin = EVE_VALUE(1);

  auto const std__rec = [](EVE_VALUE x) { return EVE_VALUE(1/x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__rec) , xp, std__rec, arg0);
  run<EVE_VALUE> (EVE_NAME(eve:rec) , xp, eve::raw(eve::rec), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve:rec) , xp, eve::raw(eve::rec), arg0);
}
