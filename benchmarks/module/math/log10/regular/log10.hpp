//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log10.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0);
  auto lmax = EVE_VALUE(eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__log10 = [](auto x){return std::log(x)*EVE_VALUE(4.34294481903252e-01);};

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__log10) , xp, std__log10 , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::log10) , xp, eve::log10 , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::log10) , xp, eve::log10 , arg0);

}
