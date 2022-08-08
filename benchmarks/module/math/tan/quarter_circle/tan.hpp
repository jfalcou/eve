//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/constant/pio_4.hpp>

int main()
{
  auto lmax = eve::pio_4(eve::as<EVE_VALUE>());
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__tan = [](auto x){return std::tan(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__tan) , xp, std__tan , arg0);
  run<EVE_VALUE>(EVE_NAME(quarter_circle(eve::tan)) , xp, eve::quarter_circle(eve::tan) , arg0);
  run<EVE_TYPE> (EVE_NAME(quarter_circle(eve::tan)) , xp, eve::quarter_circle(eve::tan) , arg0);
}
