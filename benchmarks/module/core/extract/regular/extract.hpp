//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/extract.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmin = eve::Valmax<EVE_VALUE>();
  auto lmax = eve::Valmin<EVE_VALUE>();
  int N = eve::cardinal_v<EVE_TYPE>;
   EVE_REGISTER_BENCHMARK(eve::extract, EVE_TYPE
                         , eve::bench::random<EVE_TYPE>(lmin, lmax)
                         , eve::bench::random<int>(0, N));

  eve::bench::start_benchmarks(argc, argv);
}
