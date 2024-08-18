//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);
  auto const std__bit_ceil = [](auto x) {
    if constexpr(std::is_integral_v<decltype(x)>)
       return std::bit_ceil(x);
    else return x;
  };

  eve::bench::experiment xp;
  using v_t = EVE_VALUE;
  if constexpr(std::is_integral_v<v_t>)
  {
    run<EVE_VALUE> (EVE_NAME(std__bit_floor) , xp, std__bit_ceil, arg0);
  }

  run<EVE_VALUE> (EVE_NAME(bit_ceil) , xp, eve::bit_ceil, arg0);
  run<EVE_TYPE>  (EVE_NAME(bit_ceil) , xp, eve::bit_ceil, arg0);
}
