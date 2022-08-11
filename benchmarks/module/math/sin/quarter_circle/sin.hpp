//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
  auto std__sin = [](auto x){return std::sin(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__sin) , xp, std__sin , arg0);
  run<EVE_VALUE>(EVE_NAME(quarter_circle(eve::sin)) , xp, eve::quarter_circle(eve::sin) , arg0);
  run<EVE_TYPE> (EVE_NAME(quarter_circle(eve::sin)) , xp, eve::quarter_circle(eve::sin) , arg0);
}
