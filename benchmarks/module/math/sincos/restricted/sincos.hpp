//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/constant/pio_4.hpp>

int main()
{
  auto lmax = eve::Pio_4<EVE_VALUE>();
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(eve::restricted_(eve::sincos)) , xp, eve::restricted_(eve::sincos) , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::restricted_(eve::sincos)) , xp, eve::restricted_(eve::sincos) , arg0);
}
