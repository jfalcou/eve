//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atanpi.hpp>
#include <eve/function/radinpi.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-5);
  auto lmax = EVE_VALUE(5);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__atanpi = [](auto x){return eve::radinpi(std::atan(x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__atanpi) , xp, std__atanpi , arg0);
  run<EVE_VALUE>(EVE_NAME(atanpi) , xp, eve::atanpi , arg0);
  run<EVE_TYPE> (EVE_NAME(atanpi) , xp, eve::atanpi , arg0);
}
