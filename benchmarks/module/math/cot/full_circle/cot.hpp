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
  auto lmax = eve::detail::Rempio2_limit(eve::full_circle_type(), eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__cot = [](auto x){return 1/std::tan(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__cot) , xp, std__cot , arg0);
  run<EVE_VALUE>(EVE_NAME(full_circle(eve::cot)) , xp, eve::full_circle(eve::cot) , arg0);
  run<EVE_TYPE> (EVE_NAME(full_circle(eve::cot)) , xp, eve::full_circle(eve::cot) , arg0);

}
