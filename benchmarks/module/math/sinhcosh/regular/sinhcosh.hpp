//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinhcosh.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>

int main()
{
  auto lmin = EVE_VALUE(eve::Minlog<EVE_VALUE>());
  auto lmax = EVE_VALUE(eve::Maxlog<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(sinhcosh) , xp, eve::sinhcosh , arg0);
  run<EVE_TYPE> (EVE_NAME(sinhcosh) , xp, eve::sinhcosh , arg0);

}
