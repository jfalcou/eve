//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asind.hpp>
#include <eve/function/radindeg.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asind = [](auto x){return  eve::radindeg(std::asin(x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asind) , xp, std__asind , arg0);
  run<EVE_VALUE>(EVE_NAME(asind) , xp, eve::asind , arg0);
  run<EVE_TYPE> (EVE_NAME(asind) , xp, eve::asind , arg0);
}
