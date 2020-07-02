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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  using L_VALUE = eve::logical<EVE_VALUE>;

  auto arg00 = eve::bench::random_<EVE_VALUE>(0, 1);
  auto arg0 = eve::bench::random_<L_VALUE>(0, 1);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(eve::div) , xp, eve::div, arg0, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(eve::div) , xp, eve::div, arg0, arg1, arg2);
  run<EVE_VALUE>(EVE_NAME(eve::div) , xp, eve::div, arg00, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(eve::div) , xp, eve::div, arg00, arg1, arg2);

}
