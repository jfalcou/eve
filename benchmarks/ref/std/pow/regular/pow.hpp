//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_pow = [](auto x, auto y) { return std::pow(x, y); };
  auto lmin = EVE_TYPE(-10);
  auto lmax = EVE_TYPE(10);
  EVE_REGISTER_BENCHMARK(std_pow, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
