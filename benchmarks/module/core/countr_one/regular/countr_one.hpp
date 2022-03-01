//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
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
