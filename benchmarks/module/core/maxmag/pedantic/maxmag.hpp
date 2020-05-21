//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/maxmag.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmaxmag = eve::Valmax<EVE_VALUE>();
  EVE_REGISTER_BENCHMARK(eve::pedantic_(eve::maxmag), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmaxmag)
                        , eve::bench::random<EVE_TYPE>(lmin,lmaxmag));

  eve::bench::start_benchmarks(argc, argv);
}
