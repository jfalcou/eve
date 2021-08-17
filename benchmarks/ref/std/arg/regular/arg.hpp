//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <numbers>

int main(int argc, char** argv)
{
  auto const std_arg = [](auto x) { return std::signbit(x) ? std::numbers::pi_v<EVE_TYPE> : EVE_TYPE(0); };


  EVE_REGISTER_BENCHMARK(std_arg, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
