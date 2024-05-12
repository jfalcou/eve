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
  auto std__is_lessgreater =  [](EVE_VALUE x,  EVE_VALUE y) -> eve::logical<EVE_VALUE> {return std::islessgreater(x, y); };

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(std__is_lessgreater) , xp, std__is_lessgreater, arg0, arg1);
  run<EVE_VALUE>(EVE_NAME(is_lessgreater) , xp, eve::is_lessgreater, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(is_lessgreater) , xp, eve::is_lessgreater, arg0, arg1);
}
