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
  auto const std_cot = [inrad](auto x) { return inrad*std::cos(x); };
  auto lmax = EVE_TYPE(90);
  auto lmin = EVE_TYPE(-lmax);
  EVE_REGISTER_BENCHMARK(std_cot, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
