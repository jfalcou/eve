//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <cmath>

int main()
{
  auto lmin = EVE_VALUE(0.0);
  auto lmax = EVE_VALUE(27.0);

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto std_tgamma =  [](auto x){return std::tgamma(x); };
  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std_tgamma) , xp, std_tgamma , arg0);
  run<EVE_VALUE>(EVE_NAME(tgamma) , xp, eve::tgamma , arg0);
  run<EVE_TYPE> (EVE_NAME(tgamma) , xp, eve::tgamma , arg0);
  run<EVE_VALUE>(EVE_NAME(tgamma[eve::raw]) , xp, eve::tgamma[eve::raw] , arg0);
  run<EVE_TYPE> (EVE_NAME(tgamma[eve::raw]) , xp, eve::tgamma[eve::raw] , arg0);
  run<EVE_VALUE>(EVE_NAME(tgamma[eve::fast]) , xp, eve::tgamma[eve::fast] , arg0);
  run<EVE_TYPE> (EVE_NAME(tgamma[eve::fast]) , xp, eve::tgamma[eve::fast] , arg0);

}
