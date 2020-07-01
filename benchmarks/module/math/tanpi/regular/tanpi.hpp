//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanpi.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::Valmin<EVE_VALUE>());
  auto lmax = EVE_VALUE(eve::Valmax<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__tanpi = [](auto x){return eve::radindeg(std::cos(x));};

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__tanpi) , xp, std__tanpi , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::tanpi) , xp, eve::tanpi , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::tanpi) , xp, eve::tanpi , arg0);

}
