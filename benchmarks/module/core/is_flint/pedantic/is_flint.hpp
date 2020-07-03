//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_flint.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/maxflint.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto const std__is_flint = [](EVE_VALUE x) { return std::abs(x) < eve::Maxflint<EVE_TYPE>() && !(x-std::trunc(x)); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_flint) , xp, std__is_flint, arg0);
  run<EVE_VALUE> (EVE_NAME(pedantic_(eve::is_flint)) , xp, eve::pedantic_(eve::is_flint), arg0);
  run<EVE_TYPE>  (EVE_NAME(pedantic_(eve::is_flint)) , xp, eve::pedantic_(eve::is_flint), arg0);
}
