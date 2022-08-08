//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__is_even = [](EVE_VALUE x) -> eve::logical<EVE_VALUE>  {
    if constexpr(std::is_integral_v<EVE_TYPE>)
    {
      return  !(static_cast<int>(x)&1);
    }
    else
    {
      return  !(x/2-std::trunc(x/2));
    }
  };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_even) , xp, std__is_even, arg0);
  run<EVE_VALUE> (EVE_NAME(is_even) , xp, eve::is_even, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_even) , xp, eve::is_even, arg0);
}
