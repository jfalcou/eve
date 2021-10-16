//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::detail::Rempio2_limit(eve::half_circle_type(), eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__cos = [](auto x){return std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__cos) , xp, std__cos , arg0);
  run<EVE_VALUE>(EVE_NAME(half_circle(eve::cos)) , xp, eve::half_circle(eve::cos) , arg0);
  run<EVE_TYPE> (EVE_NAME(half_circle(eve::cos)) , xp, eve::half_circle(eve::cos) , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::cos)        , xp, eve::cos             , arg0);
  run<EVE_TYPE >(EVE_NAME(eve::cos)        , xp, eve::cos             , arg0);

}
