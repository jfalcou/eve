//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
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
  auto lmin = EVE_VALUE(0);

  auto const std__sqrt = [](EVE_VALUE x) { return EVE_VALUE(std::sqrt(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__sqrt) , xp, std__sqrt, arg0);
  run<EVE_VALUE> (EVE_NAME(eve::raw(eve::sqrt)) , xp, eve::raw(eve::sqrt), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve::raw(eve::sqrt)) , xp, eve::raw(eve::sqrt), arg0);
}
