//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numbers>

int main(int argc, char** argv)
{
  auto const std_cot = [](auto x) { return 1/std::tan(x); };

  EVE_REGISTER_BENCHMARK(std_cot, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::valmin(eve::as<EVE_TYPE>()), eve::valmax(eve::as<EVE_TYPE>())));

  eve::bench::start_benchmarks(argc, argv);
}
