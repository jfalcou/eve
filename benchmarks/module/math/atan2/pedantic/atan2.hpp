//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/pedantic/atan2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::valmin(eve::as<EVE_VALUE>()));
  auto lmax = EVE_VALUE(eve::valmax(eve::as<EVE_VALUE>()));

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__atan2 = [](auto x, auto y){return std::atan2(x, y);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__atan2) , xp, std__atan2 , arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(pedantic(eve::atan2)) , xp, eve::pedantic(eve::atan2) , arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pedantic(eve::atan2)) , xp, eve::pedantic(eve::atan2) , arg0, arg1);

}
