//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqrt.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main()
{
  auto lmax = [](){
    if constexpr(eve::floating_value<EVE_VALUE>) return eve::oneotwoeps(eve::as<EVE_VALUE>());
    else return eve::Valmax<EVE_VALUE>();
  }();
  auto lmin = EVE_VALUE(0);

  auto const std__sqrt = [](EVE_VALUE x) { return EVE_VALUE(std::sqrt(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__sqrt) , xp, std__sqrt, arg0);
  run<EVE_VALUE> (EVE_NAME(eve::raw_(eve::sqrt)) , xp, eve::raw_(eve::sqrt), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve::raw_(eve::sqrt)) , xp, eve::raw_(eve::sqrt), arg0);
}
