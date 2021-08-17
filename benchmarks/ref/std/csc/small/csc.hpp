//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/pio_2.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto lmax = eve::pio_2(eve::as<EVE_TYPE>());
  auto lmin = -lmax;
  auto const std_csc = [](auto x) { return 1/std::sin(x); };
  EVE_REGISTER_BENCHMARK(std_csc, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
