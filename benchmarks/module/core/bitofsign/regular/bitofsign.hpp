//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__bitofsign = [](auto x) { return (std::signbit(x)) ? EVE_TYPE(-0.0) : EVE_TYPE(0.0); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__bitofsign) , xp, std__bitofsign, arg0);
  run<EVE_VALUE> (EVE_NAME(bitofsign) , xp, eve::bitofsign, arg0);
  run<EVE_TYPE>  (EVE_NAME(bitofsign) , xp, eve::bitofsign, arg0);
}
