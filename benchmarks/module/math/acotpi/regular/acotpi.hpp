//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-5);
  auto lmax = EVE_VALUE(5);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acotpi = [](auto x){return std::atan(1/x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acotpi) , xp, std__acotpi , arg0);
  run<EVE_VALUE>(EVE_NAME(acotpi) , xp, eve::acotpi , arg0);
  run<EVE_TYPE> (EVE_NAME(acotpi) , xp, eve::acotpi , arg0);
}
