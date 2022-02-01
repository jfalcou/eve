//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/bit_select.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg1 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto arg2 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  if constexpr(eve::integral_value<EVE_VALUE>)
  {
    auto std__bit_select =  [](auto x,  auto y, auto z){return EVE_VALUE((x&y) | (~x&z)); };

    run<EVE_VALUE>(EVE_NAME(std__bit_select) , xp, std__bit_select, arg0, arg1, arg2);
  }

  run<EVE_VALUE>(EVE_NAME(bit_select) , xp, eve::bit_select, arg0, arg1, arg2);
  run<EVE_TYPE> (EVE_NAME(bit_select) , xp, eve::bit_select, arg0, arg1, arg2);
}
