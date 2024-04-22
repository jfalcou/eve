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
  auto lmax = eve::Rempio2_limit[eve::half_circle2](eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__cos = [](auto x){return std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__cos) , xp, std__cos , arg0);
  run<EVE_VALUE>(EVE_NAME(cos[eve::half_circle2]) , xp, eve::cos[eve::half_circle2] , arg0);
  run<EVE_TYPE> (EVE_NAME(cos[eve::half_circle2]) , xp, eve::cos[eve::half_circle2] , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::cos)        , xp, eve::cos             , arg0);
  run<EVE_TYPE >(EVE_NAME(eve::cos)        , xp, eve::cos             , arg0);

}
