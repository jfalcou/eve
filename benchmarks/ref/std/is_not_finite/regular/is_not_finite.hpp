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
  auto const std_is_not_finite = [](auto x) { return !(std::isinf(x) || std::isnan(x)); };

  EVE_REGISTER_BENCHMARK(std_is_not_finite, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
