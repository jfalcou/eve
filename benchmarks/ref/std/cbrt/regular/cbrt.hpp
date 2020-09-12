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

#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto const std_cbrt = [](auto x) { return std::cbrt(x); };
  auto l = eve::valmax(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_cbrt, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
