//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/special.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0.0);
  auto lmax = EVE_VALUE(27.0);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std_exp_int =  [](auto x){return std::expint(x); };
  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_exp_int) , xp, std_exp_int , arg0);
  run<EVE_VALUE>(EVE_NAME(exp_int) , xp, eve::exp_int , arg0);
  run<EVE_TYPE> (EVE_NAME(exp_int) , xp, eve::exp_int , arg0);
  run<EVE_VALUE>(EVE_NAME(exp_int[eve::raw]) , xp, eve::exp_int[eve::raw] , arg0);
  run<EVE_TYPE> (EVE_NAME(exp_int[eve::raw]) , xp, eve::exp_int[eve::raw] , arg0);
  run<EVE_VALUE>(EVE_NAME(exp_int[eve::fast]) , xp, eve::exp_int[eve::fast] , arg0);
  run<EVE_TYPE> (EVE_NAME(exp_int[eve::fast]) , xp, eve::exp_int[eve::fast] , arg0);

}
