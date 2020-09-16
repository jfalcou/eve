//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/convert.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>
//THE BENCH IS VERY PARTIAL just type  to signed integer type of same size
int main()
{
  auto lmin = eve::valmin(eve::as<EVE_VALUE>())/2;
  auto lmax = eve::valmax(eve::as<EVE_VALUE>())/2;
  using i_t = eve::detail::as_integer_t<EVE_VALUE, signed>;
  auto f =  [](auto x){ return eve::convert(x, eve::as_<i_t>());
  }
 ;
  auto arg0 = eve::bench::random_<EVE_VALUE>(lmin,lmax);

  eve::bench::experiment xp;
  run<EVE_VALUE>(EVE_NAME(convert) , xp, f, arg0);

}
