//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/pio_4.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_sin = [](auto x) { return std::sin(x); };

  EVE_REGISTER_BENCHMARK(std_sin, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::pio_4(eve::as<EVE_TYPE>()), eve::pio_4(eve::as<EVE_TYPE>())));

  eve::bench::start_benchmarks(argc, argv);
}
