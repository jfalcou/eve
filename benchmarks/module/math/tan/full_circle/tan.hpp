//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::detail::Rempio2_limit(eve::full_circle_type(), eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__tan = [](auto x){return std::tan(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__tan) , xp, std__tan , arg0);
  run<EVE_VALUE>(EVE_NAME(full_circle(eve::tan)) , xp, eve::full_circle(eve::tan) , arg0);
  run<EVE_TYPE> (EVE_NAME(full_circle(eve::tan)) , xp, eve::full_circle(eve::tan) , arg0);

}
