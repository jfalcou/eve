//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_odd.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();

  auto const std__is_odd = [](EVE_VALUE x) {
    if constexpr(std::is_integral_v<EVE_TYPE>)
    {
      return  (static_cast<int>(x)&1);
    }
    else
    {
      --x;
      return  !(x/2-std::trunc(x/2));
    }
  };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__is_odd) , xp, std__is_odd, arg0);
  run<EVE_VALUE> (EVE_NAME(is_odd) , xp, eve::is_odd, arg0);
  run<EVE_TYPE>  (EVE_NAME(is_odd) , xp, eve::is_odd, arg0);
}
