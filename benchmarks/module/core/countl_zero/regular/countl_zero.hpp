//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <bit>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__countl_zero = [](EVE_VALUE x) { return std::countl_zero(x); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__countl_zero) , xp, std__countl_zero, arg0);
  run<EVE_VALUE> (EVE_NAME(countl_zero) , xp, eve::countl_zero, arg0);
  run<EVE_TYPE>  (EVE_NAME(countl_zero) , xp, eve::countl_zero, arg0);
}
