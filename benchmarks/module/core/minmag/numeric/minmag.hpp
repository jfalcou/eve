//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minmag.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valminmag.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lminmag = eve::Valminmag<EVE_VALUE>();
  EVE_REGISTER_BENCHMARK(eve::numeric_(eve::minmag), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lminmag)
                        , eve::bench::random<EVE_TYPE>(lmin,lminmag));

  eve::bench::start_benchmarks(argc, argv);
}
