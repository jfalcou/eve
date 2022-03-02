//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/special.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-27.0);
  auto lmax = EVE_VALUE(27.0);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std_erf =  [](auto x){return std::erf(x); };
  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_erf) , xp, std_erf , arg0);
  run<EVE_VALUE>(EVE_NAME(erf) , xp, eve::erf , arg0);
  run<EVE_TYPE> (EVE_NAME(erf) , xp, eve::erf , arg0);

}
