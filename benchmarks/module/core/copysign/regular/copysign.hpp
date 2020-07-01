//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/copysign.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__copysign =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(std::copysign(x, y)); };

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__copysign) , xp, std__copysign, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(eve::copysign) , xp, eve::copysign, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(eve::copysign) , xp, eve::copysign, arg0, arg1);
}
