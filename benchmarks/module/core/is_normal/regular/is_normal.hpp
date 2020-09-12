//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_normal.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_normal = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  { return std::fpclassify(x) ==  FP_NORMAL; };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_normal) , xp, std__is_normal, arg0);
  run<EVE_VALUE> (EVE_NAME(is_normal) , xp, eve::is_normal, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_normal) , xp, eve::is_normal, arg0);
}
