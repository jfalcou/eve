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
  auto lmax = eve::Rempio2_limit[eve::full_circle](eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__tan = [](auto x){return std::tan(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__tan     ) , xp, std__tan , arg0);
  run<EVE_VALUE>(EVE_NAME(tan full     ) , xp, eve::tan[eve::full_circle] , arg0);
  run<EVE_TYPE> (EVE_NAME(tan full     ) , xp, eve::tan[eve::full_circle] , arg0);
  run<EVE_TYPE> (EVE_NAME(tan full_raw ) , xp, eve::tan[eve::full_circle][eve::raw] , arg0);
  run<EVE_TYPE> (EVE_NAME(tan full_fast) , xp, eve::tan[eve::full_circle][eve::fast] , arg0);

}
