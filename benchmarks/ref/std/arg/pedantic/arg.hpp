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
#include <numbers>

int main(int argc, char** argv)
{
  auto const std_arg = [](auto x) { if (std::isnan(x)) return x;
                                    return std::signbit(x) ? std::numbers::pi_v<EVE_TYPE> : EVE_TYPE(0); };

  EVE_REGISTER_BENCHMARK(std_arg, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
