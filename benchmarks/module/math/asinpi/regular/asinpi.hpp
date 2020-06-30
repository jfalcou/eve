//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinpi.hpp>
#include <eve/function/radinpi.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asinpi = [](auto x){return  eve::radinpi(std::asin(x));};

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__asinpi) , xp, std__asinpi , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asinpi) , xp, eve::asinpi , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asinpi) , xp, eve::asinpi , arg0);
}
