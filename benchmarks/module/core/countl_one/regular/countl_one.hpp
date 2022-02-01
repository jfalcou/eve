//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/countl_one.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <bit>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__countl_one = [](EVE_VALUE x) { return std::countl_one(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__countl_one) , xp, std__countl_one, arg0);
  run<EVE_VALUE> (EVE_NAME(countl_one) , xp, eve::countl_one, arg0);
  run<EVE_TYPE>  (EVE_NAME(countl_one) , xp, eve::countl_one, arg0);
}
