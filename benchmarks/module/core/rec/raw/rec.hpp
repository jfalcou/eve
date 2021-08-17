//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmax = [](){
    if constexpr(eve::floating_value<EVE_VALUE>) return eve::oneotwoeps(eve::as<EVE_VALUE>());
    else return eve::valmax(eve::as<EVE_VALUE>());
  }();
  auto lmin = EVE_VALUE(0);

  auto const std__rec = [](EVE_VALUE x) { return EVE_VALUE(1/x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__rec) , xp, std__rec, arg0);
  run<EVE_VALUE> (EVE_NAME(eve:rec) , xp, eve::raw(eve::rec), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve:rec) , xp, eve::raw(eve::rec), arg0);
}
