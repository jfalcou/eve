//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_or.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  if constexpr(eve::integral_value<EVE_VALUE>)
  {
    auto std__logical_or =  [](auto x,  auto y){return EVE_VALUE(x||y); };

    run<EVE_VALUE>(EVE_NAME(std__logical_or) , xp, std__logical_or, arg0, arg1);
  }

  run<EVE_VALUE>(EVE_NAME(logical_or) , xp, eve::logical_or, arg0, arg1);
  run<EVE_TYPE> (EVE_NAME(logical_or) , xp, eve::logical_or, arg0, arg1);
}
