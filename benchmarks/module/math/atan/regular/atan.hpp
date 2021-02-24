//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-5);
  auto lmax = EVE_VALUE(5);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__atan = [](auto x){return std::atan(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__atan) , xp, std__atan , arg0);
  run<EVE_VALUE>(EVE_NAME(atan) , xp, eve::atan , arg0);
  run<EVE_TYPE> (EVE_NAME(atan) , xp, eve::atan , arg0);
}
