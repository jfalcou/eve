//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__mul =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(x+y); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std::mul) , xp, std__mul, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(mul) , xp, eve::mul, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(mul) , xp, eve::mul, arg0, arg1);
}
