//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::Rempio2_limit[eve::full_circle2](eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__csc = [](auto x){return 1/std::sin(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__csc) , xp, std__csc , arg0);
  run<EVE_VALUE>(EVE_NAME(csc[eve::full_circle2]) , xp, eve::csc[eve::full_circle2] , arg0);
  run<EVE_TYPE> (EVE_NAME(csc[eve::full_circle2]) , xp, eve::csc[eve::full_circle2] , arg0);

}
