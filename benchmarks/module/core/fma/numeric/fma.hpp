//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <numeric>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  auto std__fma =  [](EVE_VALUE x,  EVE_VALUE y, auto z){return EVE_VALUE(std::fma(x, y, z)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__fma) , xp, std__fma, arg0, arg1, arg2);
  run<EVE_VALUE>(EVE_NAME(numeric(eve::fma)) , xp, eve::numeric(eve::fma), arg0, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(numeric(eve::fma)) , xp, eve::numeric(eve::fma), arg0, arg1, arg2);
}
