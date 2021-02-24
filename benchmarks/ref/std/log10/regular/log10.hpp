//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <cmath>
#include <numbers>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>

int main(int argc, char** argv)
{
  EVE_TYPE log10 = std::numbers::ln10_v<EVE_TYPE>;
  auto const std_log10 = [log10](auto x) { return std::log(x)/log10; };
  auto lmin = eve::minlog(eve::as<EVE_TYPE>());
  auto lmax = eve::maxlog(eve::as<EVE_TYPE>());

  EVE_REGISTER_BENCHMARK(std_log10, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
