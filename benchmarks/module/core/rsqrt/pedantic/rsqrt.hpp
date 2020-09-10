//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rsqrt.hpp>
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

  auto const std__rsqrt = [](EVE_VALUE x) { return EVE_VALUE(1/std::sqrt(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__rsqrt) , xp, std__rsqrt, arg0);
  run<EVE_VALUE> (EVE_NAME(eve::pedantic_(eve::rsqrt)) , xp, eve::pedantic_(eve::rsqrt), arg0);
  run<EVE_TYPE>  (EVE_NAME(eve::pedantic_(eve::rsqrt)) , xp, eve::pedantic_(eve::rsqrt), arg0);
}
