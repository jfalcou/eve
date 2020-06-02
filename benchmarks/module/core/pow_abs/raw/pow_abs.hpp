//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <cmath>
#include <eve/function/pow_abs.hpp>

int main(int argc, char** argv)
{
  auto const std_pow = [](auto x, auto y) { return eve::raw_(eve::pow_abs)(x, y); };
  auto lmin = EVE_TYPE(-10);
  auto lmax = EVE_TYPE(10);
  EVE_REGISTER_BENCHMARK(std_pow, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
