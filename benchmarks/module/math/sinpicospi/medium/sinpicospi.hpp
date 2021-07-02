//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpicospi.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmax = eve::detail::Rempio2_limit(eve::medium_type(), eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(medium(eve::sinpicospi)) , xp, eve::medium(eve::sinpicospi) , arg0);
  run<EVE_TYPE> (EVE_NAME(medium(eve::sinpicospi)) , xp, eve::medium(eve::sinpicospi) , arg0);

}
