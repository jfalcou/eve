//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/constant/pio_4.hpp>

int main()
{
  auto lmax = eve::Pio_4<EVE_VALUE>();
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__sec = [](auto x){return 1/std::cos(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__sec) , xp, std__sec , arg0);
  run<EVE_VALUE>(EVE_NAME(restricted_(eve::sec)) , xp, eve::restricted_(eve::sec) , arg0);
  run<EVE_TYPE> (EVE_NAME(restricted_(eve::sec)) , xp, eve::restricted_(eve::sec) , arg0);
}
