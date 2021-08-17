//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto const std_acot = [](auto x) { return std::atan(1/x); };
  auto lmin = EVE_TYPE(-5);
  auto lmax = EVE_TYPE(5);

  EVE_REGISTER_BENCHMARK(std_acot, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
