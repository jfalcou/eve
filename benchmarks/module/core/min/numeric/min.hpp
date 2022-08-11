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
  auto std__min =  [](EVE_VALUE x,  EVE_VALUE y){return EVE_VALUE(std::min(x, y)); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__min) , xp, std__min, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(numeric(eve::min)) , xp, eve::numeric(eve::min), arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(numeric(eve::min)) , xp, eve::numeric(eve::min), arg0, arg1);
}
