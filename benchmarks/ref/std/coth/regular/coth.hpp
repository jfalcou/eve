//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_coth = [](auto x) { return 1/std::tan(x); };
  auto lmin = eve::maxlog(eve::as<EVE_TYPE>());
  auto lmax = eve::minlog(eve::as<EVE_TYPE>());
   EVE_REGISTER_BENCHMARK(std_coth, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
