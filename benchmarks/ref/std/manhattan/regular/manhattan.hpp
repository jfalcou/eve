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
  auto const std_manhattan2 = [](auto x, auto y) { return std::abs(x)+std::abs(y); };
  auto l = eve::valmax(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_manhattan2, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(-l, l)
                        , eve::bench::random<EVE_TYPE>(-l, l));
  auto const std_manhattan3 = [](auto x, auto y, auto z) { return std::abs(x)+std::abs(y)+std::abs(z); };
   EVE_REGISTER_BENCHMARK(std_manhattan3, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(-l, l)
                        , eve::bench::random<EVE_TYPE>(-l, l)
                        , eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
