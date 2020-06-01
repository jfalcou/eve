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
  auto const std_acot = [](auto x) { return std::atan(1/x); };
  auto lmin = EVE_TYPE(1);
  auto lmax = eve::Valmax<EVE_TYPE>();

  EVE_REGISTER_BENCHMARK(std_acot, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
