//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__if_else =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(x ? y : EVE_VALUE(01)); };
  auto eve__if_else =  [](auto x,  auto y){return eve::if_else(x, y, eve::zero_); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__if_else) , xp, std__if_else, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(eve__if_else) , xp, eve__if_else, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(eve__if_else) , xp, eve__if_else, arg0, arg1);
}
