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

  auto std__fdim =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(std::fdim(x, y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__fdim) , xp, std__fdim, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(fdim) , xp, eve::fdim, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(fdim) , xp, eve::fdim, arg0, arg1);
}
