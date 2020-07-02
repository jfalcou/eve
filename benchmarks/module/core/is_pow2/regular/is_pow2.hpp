//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <bit>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto const std__is_pow2 = [](EVE_VALUE x) { return std::hasonebitset; };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE> (EVE_NAME(std__is_pow2) , xp, std__is_pow2, arg0);
  run<EVE_VALUE> (EVE_NAME(eve::is_pow2) , xp, eve::is_pow2, arg0);
  run<EVE_TYPE>  (EVE_NAME(eve::is_pow2) , xp, eve::is_pow2, arg0);
}
