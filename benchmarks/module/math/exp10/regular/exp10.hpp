//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/constant/maxlog10.hpp>
#include <eve/module/math/constant/minlog10.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::minlog10(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::maxlog10(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__exp10 = [](auto x){return std::exp(x*EVE_VALUE(2.30258509299405e+00));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__exp10) , xp, std__exp10 , arg0);
  run<EVE_VALUE>(EVE_NAME(exp10) , xp, eve::exp10 , arg0);
  run<EVE_TYPE> (EVE_NAME(exp10) , xp, eve::exp10 , arg0);

}
