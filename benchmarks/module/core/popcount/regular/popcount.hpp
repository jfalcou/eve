//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());
  using ui_t = eve::as_integer_t<EVE_VALUE, unsigned>;
  auto const std__popcount = [](EVE_VALUE x) { return std::popcount(eve::bit_cast(x, eve::as<ui_t>())); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__popcount) , xp, std__popcount, arg0);
  run<EVE_VALUE> (EVE_NAME(popcount) , xp, eve::popcount, arg0);
  run<EVE_TYPE>  (EVE_NAME(popcount) , xp, eve::popcount, arg0);
}
