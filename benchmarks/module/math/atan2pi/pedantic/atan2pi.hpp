//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/atan2pi.hpp>
#include <eve/function/radinpi.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::valmin(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__atan2pi = [](auto x, auto y){return eve::radinpi(std::atan2(x, y));};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__atan2pi) , xp, std__atan2pi , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(pedantic(eve::atan2pi)) , xp, eve::pedantic(eve::atan2pi) , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pedantic(eve::atan2pi)) , xp, eve::pedantic(eve::atan2pi) , arg0, arg1);

}
