//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/atand.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-5);
  auto lmax = EVE_VALUE(5);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__atand = [](auto x){return eve::radindeg(std::atan(x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__atand) , xp, std__atand , arg0);
  run<EVE_VALUE>(EVE_NAME(atand) , xp, eve::atand , arg0);
  run<EVE_TYPE> (EVE_NAME(atand) , xp, eve::atand , arg0);
}
