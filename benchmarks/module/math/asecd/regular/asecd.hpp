//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/asecd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/math/constant/oneotwoeps.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(1);
  auto lmax = EVE_VALUE(eve::oneotwoeps(eve::as<EVE_VALUE>())); //eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__asecd = [](auto x){return eve::radindeg(std::acos(1/x));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__asecd) , xp, std__asecd , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::asecd) , xp, eve::asecd , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::asecd) , xp, eve::asecd , arg0);
}
