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
#include <eve/constant/pio_4.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_cospi = [](auto x) { return std::cospi(x); };

  EVE_REGISTER_BENCHMARK(std_cospi, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::Pio_4<EVE_TYPE>(), eve::Pio_4<EVE_TYPE>()));

  eve::bench::start_benchmarks(argc, argv);
}
