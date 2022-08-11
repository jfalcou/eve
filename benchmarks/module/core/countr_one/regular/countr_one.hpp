//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <bit>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__countr_one = [](EVE_VALUE x) { return std::countr_one(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__countr_one) , xp, std__countr_one, arg0);
  run<EVE_VALUE> (EVE_NAME(countr_one) , xp, eve::countr_one, arg0);
  run<EVE_TYPE>  (EVE_NAME(countr_one) , xp, eve::countr_one, arg0);
}
