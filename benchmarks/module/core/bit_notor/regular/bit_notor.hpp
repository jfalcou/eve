//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notor.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  if constexpr(eve::integral_value<EVE_VALUE>)
  {
    auto std__bit_notor =  [](auto x,  auto y){return EVE_VALUE(~x|y); };

    run<EVE_VALUE>(EVE_NAME(std__bit_notor) , xp, std__bit_notor, arg0, arg1);
  }

  run<EVE_VALUE>(EVE_NAME(bit_notor) , xp, eve::bit_notor, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(bit_notor) , xp, eve::bit_notor, arg0, arg1);
}
