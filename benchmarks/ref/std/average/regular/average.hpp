//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main(int argc, char** argv)
{
  auto const std_average = [](auto x, auto y) { return std::midpoint(x, y); };
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_average, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
