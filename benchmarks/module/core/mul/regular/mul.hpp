//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main()
{
  EVE_VALUE lmin = 1;
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(eve::mul) , xp, eve::mul, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(eve::mul) , xp, eve::mul, arg0, arg1);
}
