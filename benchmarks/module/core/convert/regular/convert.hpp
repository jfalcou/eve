//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <cmath>
//THE BENCH IS VERY PARTIAL just type  to signed integer type of same size
int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>())/2;
  auto lmax = eve::valmax(eve::as<EVE_VALUE>())/2;
  using i_t = eve::as_integer_t<EVE_VALUE, signed>;
  auto f =  [](auto x){ return eve::convert(x, eve::as<i_t>());
  }
 ;
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(convert) , xp, f, arg0);

}
