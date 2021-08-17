//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asin = [](auto x){return std::asin(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asin) , xp, std__asin , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asin) , xp, eve::asin , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asin) , xp, eve::asin , arg0);
}
