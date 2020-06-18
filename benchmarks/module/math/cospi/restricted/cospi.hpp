//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cospi.hpp>
#include <eve/constant/pio_4.hpp>
#include <cmath>
#include <eve/concept/value.hpp>


int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  if (eve::floating_value<EVE_TYPE>)
  {
    auto lmax = EVE_VALUE(0.25);
    auto lmin = EVE_VALUE(-0.25);
    EVE_REGISTER_BENCHMARK(eve::restricted_(eve::cospi), EVE_TYPE
                          , eve::bench::random<EVE_TYPE>(lmin,lmax));

    eve::bench::start_benchmarks(argc, argv);
  }

}
