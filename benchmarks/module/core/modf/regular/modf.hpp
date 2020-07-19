//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/modf.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto const std__modf = [](EVE_VALUE x) { EVE_VALUE i; auto f = std::modf(x, &i); return std::make_tuple(f, i); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__modf) , xp, std__modf, arg0);
  run<EVE_VALUE> (EVE_NAME(modf) , xp, eve::modf, arg0);
  run<EVE_TYPE>  (EVE_NAME(modf) , xp, eve::modf, arg0);
}
