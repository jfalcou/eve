//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <numbers>

int main(int argc, char** argv)
{
  auto const std_cot = [](auto x) { return 1/std::tan(x); };
  auto l = std::numbers::pi_v<EVE_TYPE>/4;
  EVE_REGISTER_BENCHMARK(std_cot, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
