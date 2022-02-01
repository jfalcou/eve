//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/modf.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <cmath>

int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>());
  auto lmax = eve::valmax(eve::as<EVE_VALUE>());

  auto const std__modf = [](EVE_VALUE x) { EVE_VALUE i; auto f = std::modf(x, &i); return std::make_tuple(f, i); };

  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE> (EVE_NAME(std__modf) , xp, std__modf, arg0);
  run<EVE_VALUE> (EVE_NAME(modf) , xp, eve::modf, arg0);
  run<EVE_TYPE>  (EVE_NAME(modf) , xp, eve::modf, arg0);
}
