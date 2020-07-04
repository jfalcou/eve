//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/oneotwoeps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = [](){
    if constexpr(eve::floating_value<EVE_VALUE>) return eve::Oneotwoeps<EVE_VALUE>();
    else return eve::Valmax<EVE_VALUE>();
  }();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(EVE_VALUE(1),lmax);

  auto std__div =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(x+y); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__div) , xp, std__div, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(div) , xp, eve::div, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(div) , xp, eve::div, arg0, arg1);
}
