//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/pio_2.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmax = eve::Pio_2<EVE_VALUE>();
  auto lmin = -lmax;
  EVE_REGISTER_BENCHMARK(eve::small_(eve::csc), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

}
