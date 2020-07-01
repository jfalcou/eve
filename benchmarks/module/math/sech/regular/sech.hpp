//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sech.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(eve::Minlog<EVE_VALUE>());
  auto lmax = EVE_VALUE(eve::Maxlog<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std__sech = [](auto x){return 1/std::cosh(x);};

  eve::bench::experiment xp( eve::bench::optimal_size<EVE_TYPE> );
  run<EVE_VALUE>(EVE_NAME(std__sech) , xp, std__sech , arg0);
  run<EVE_VALUE>(EVE_NAME(eve::sech) , xp, eve::sech , arg0);
  run<EVE_TYPE> (EVE_NAME(eve::sech) , xp, eve::sech , arg0);

}
