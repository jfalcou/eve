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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numbers>

int main(int argc, char** argv)
{
  constexpr EVE_TYPE inrad = std::numbers::pi_v<EVE_TYPE>/180;
  auto const std_cscd = [](auto x) { return inrad*1/std::sin(x); };

  EVE_REGISTER_BENCHMARK(std_cscd, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::Valmin<EVE_TYPE>(), eve::Valmax<EVE_TYPE>()));

  eve::bench::start_benchmarks(argc, argv);
}
