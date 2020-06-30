//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asech.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asech = [](auto x){return std::acosh(1/x);};

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__asech) , xp, std__asech , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asech) , xp, eve::asech , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asech) , xp, eve::asech , arg0);
}
