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
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_cos = [](auto x) { return std::cos(x); };

  EVE_REGISTER_BENCHMARK(std_cos, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::Valmin<EVE_TYPE>(), eve::Valmax<EVE_TYPE>()));

  eve::bench::start_benchmarks(argc, argv);
}
