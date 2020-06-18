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
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <cmath>
#include <eve/concept/value.hpp>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  if (eve::floating_value<EVE_TYPE>)
  {
    auto lmax = eve::detail::Rempio2_limit(eve::medium_type(), eve::as_<EVE_VALUE>());
    auto lmin = EVE_VALUE(-lmax);
    EVE_REGISTER_BENCHMARK(eve::medium_(eve::cospi), EVE_TYPE
                          , eve::bench::random<EVE_TYPE>(lmin,lmax));

    eve::bench::start_benchmarks(argc, argv);
  }
  else
  {
    auto lmax = eve::Valmax<EVE_VALUE>();
    auto lmin = eve::Valmin<EVE_VALUE>();
    EVE_REGISTER_BENCHMARK(eve::medium_(eve::cospi), EVE_TYPE
                          , eve::bench::random<EVE_TYPE>(lmin,lmax));

    eve::bench::start_benchmarks(argc, argv);
  }


}
