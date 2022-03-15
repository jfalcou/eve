//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::detail::Rempio2_limit(eve::half_circle_type(), eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__csc = [](auto x){return 1/std::sin(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__csc) , xp, std__csc , arg0);
  run<EVE_VALUE>(EVE_NAME(half_circle(eve::csc)) , xp, eve::half_circle(eve::csc) , arg0);
  run<EVE_TYPE> (EVE_NAME(half_circle(eve::csc)) , xp, eve::half_circle(eve::csc) , arg0);

}
