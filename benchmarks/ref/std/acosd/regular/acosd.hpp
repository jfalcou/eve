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
  constexpr EVE_TYPE indeg = EVE_TYPE(180)/std::numbers::pi_v<EVE_TYPE>;
  auto const std_acosd = [indeg](auto x) { return indeg*std::acos(x); };

  EVE_REGISTER_BENCHMARK(std_acosd, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

  eve::bench::start_benchmarks(argc, argv);
}
