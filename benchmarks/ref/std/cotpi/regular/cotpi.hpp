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
  auto const std_cotpi = [](auto x) { return 1/std::tan(std::numbers::pi_v<EVE_TYPE>*x); };

  EVE_REGISTER_BENCHMARK(std_cotpi, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::valmin(eve::as<EVE_TYPE>()), eve::valmax(eve::as<EVE_TYPE>())));

  eve::bench::start_benchmarks(argc, argv);
}
