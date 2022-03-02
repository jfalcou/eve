//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::valmin(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__cospi = [](auto x){return eve::radindeg(std::cos(x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__cospi) , xp, std__cospi , arg0);
  run<EVE_VALUE>(EVE_NAME(cospi) , xp, eve::cospi , arg0);
  run<EVE_TYPE> (EVE_NAME(cospi) , xp, eve::cospi , arg0);

}
