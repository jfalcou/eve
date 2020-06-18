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
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  auto f =  [](auto x){ return eve::convert(x, eve::as_<eve::detail::as_integer_t<EVE_VALUE, signed>>());
  }
 ;
  EVE_REGISTER_BENCHMARK(f, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

}
