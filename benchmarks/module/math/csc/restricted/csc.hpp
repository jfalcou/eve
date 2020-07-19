//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/pio_4.hpp>

int main()
{
  auto lmax = eve::Pio_4<EVE_VALUE>();
  auto lmin = -lmax;

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__csc = [](auto x){return 1/std::sin(x);};

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__csc) , xp, std__csc , arg0);
  run<EVE_VALUE>(EVE_NAME(restricted_(eve::csc)) , xp, eve::restricted_(eve::csc) , arg0);
  run<EVE_TYPE> (EVE_NAME(restricted_(eve::csc)) , xp, eve::restricted_(eve::csc) , arg0);
}
