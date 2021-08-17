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
  auto lmin = eve::maxlog(eve::as<EVE_TYPE>());
  auto lmax = eve::minlog(eve::as<EVE_TYPE>());
  auto const std_fdim = [](auto x, auto y) { return std::fdim(x, y); };

  EVE_REGISTER_BENCHMARK(std_fdim, EVE_TYPE
                         , eve::bench::random<EVE_TYPE>(lmin, lmax)
                         , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
