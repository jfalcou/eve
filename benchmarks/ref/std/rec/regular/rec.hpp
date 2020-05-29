//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto lmin = eve::Valmin<EVE_VALUE>();
  auto lmax = eve::Valmax<EVE_VALUE>();
  auto const std_rec = [](auto x) { return 1/x; };
  EVE_REGISTER_BENCHMARK(eve::rec, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
#
