//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-1);
  auto lmax = EVE_VALUE(1);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acospi = [](auto x){return eve::radinpi(std::acos(x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acospi) , xp, std__acospi , arg0);
  run<EVE_VALUE>(EVE_NAME(acospi) , xp, eve::acospi , arg0);
  run<EVE_TYPE> (EVE_NAME(acospi) , xp, eve::acospi , arg0);

}
