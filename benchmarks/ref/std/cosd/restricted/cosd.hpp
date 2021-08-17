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
  constexpr EVE_TYPE inrad = std::numbers::pi_v<EVE_TYPE>/180;
  auto const std_cosd = [inrad](auto x) { return inrad*std::cos(x); };
  auto lmax = EVE_TYPE(45);
  auto lmin = EVE_TYPE(-lmax);

  EVE_REGISTER_BENCHMARK(std_cosd, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
