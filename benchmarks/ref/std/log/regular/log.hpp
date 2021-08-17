//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <numbers>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>

int main(int argc, char** argv)
{
  auto const std_log = [](auto x) { return std::log(x); };
  auto lmin = eve::minlog(eve::as<EVE_TYPE>());
  auto lmax = eve::maxlog(eve::as<EVE_TYPE>());

  EVE_REGISTER_BENCHMARK(std_log, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
