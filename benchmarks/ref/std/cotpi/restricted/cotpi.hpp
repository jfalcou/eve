//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/pio_4.hpp>
#include <numbers>

int main(int argc, char** argv)
{
  auto const std_cotpi = [](auto x) { return 1/std::tan(std::numbers::pi_v<EVE_TYPE>*x); };

  EVE_REGISTER_BENCHMARK(std_cotpi, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::pio_4(eve::as<EVE_TYPE>()), eve::pio_4(eve::as<EVE_TYPE>())));

  eve::bench::start_benchmarks(argc, argv);
}
