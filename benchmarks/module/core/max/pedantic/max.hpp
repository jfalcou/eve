//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__max =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(std::max(x, y)); };

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__max) , xp, std__max, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(eve::pedantic_(eve::max)) , xp, eve::pedantic_(eve::max), arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(eve::pedantic_(eve::max)) , xp, eve::pedantic_(eve::max), arg0, arg1);
}
