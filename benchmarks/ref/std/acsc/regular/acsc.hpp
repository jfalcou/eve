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

int main(int argc, char** argv)
{
  auto const std_acsc = [](auto x) { return std::asin(1/x); };
  auto lmin = EVE_TYPE(1);
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());

  EVE_REGISTER_BENCHMARK(std_acsc, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
