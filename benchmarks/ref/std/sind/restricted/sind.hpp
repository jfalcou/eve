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
  constexpr EVE_TYPE inrad = std::numbers::pi_v<EVE_TYPE>/180;
  auto const std_sind = [inrad](auto x) { return inrad*std::sin(x); };
  using EVE_TYPE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmax = EVE_TYPE(45);
  auto lmin = EVE_TYPE(-lmax);

  EVE_REGISTER_BENCHMARK(std_sind, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
