//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__hypot =  [](EVE_VALUE x, EVE_VALUE y){return EVE_VALUE(std::hypot(x, y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__hypot) , xp, std__hypot, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(pedantic_(eve::hypot)) , xp, eve::pedantic_(eve::hypot), arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(pedantic_(eve::hypot)) , xp, eve::pedantic_(eve::hypot), arg0, arg1);
}
