//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/math/constant/oneotwoeps.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(-eve::oneotwoeps(eve::as<EVE_VALUE>())); //eve::valmin(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::oneotwoeps(eve::as<EVE_VALUE>())); //eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asinh = [](auto x){return std::asinh(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asinh) , xp, std__asinh , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asinh) , xp, eve::asinh , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asinh) , xp, eve::asinh , arg0);
}
