//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::detail::Rempio2_limit(eve::small_type(), eve::as_<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__sin = [](auto x){return std::sin(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__sin) , xp, std__sin , arg0);
  run<EVE_VALUE>(EVE_NAME(small(eve::sin)) , xp, eve::small(eve::sin) , arg0);
  run<EVE_TYPE> (EVE_NAME(small(eve::sin)) , xp, eve::small(eve::sin) , arg0);

}
