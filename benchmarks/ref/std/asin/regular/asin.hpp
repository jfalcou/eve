//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_asin = [](auto x) { return std::asin(x); };

  EVE_REGISTER_BENCHMARK(std_asin, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
