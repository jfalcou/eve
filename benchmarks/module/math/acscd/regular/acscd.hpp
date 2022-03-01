//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/math/constant/oneotwoeps.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(1);
  auto lmax = EVE_VALUE(eve::oneotwoeps(eve::as<EVE_VALUE>())); //eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__acscd = [](auto x){return eve::radindeg(std::acos(1/x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__acscd) , xp, std__acscd , arg0);
  run<EVE_VALUE>(EVE_NAME(acscd) , xp, eve::acscd , arg0);
  run<EVE_TYPE> (EVE_NAME(acscd) , xp, eve::acscd , arg0);
}
