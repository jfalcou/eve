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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

int main(int argc, char** argv)
{
  auto const std_hypot2 = [](auto x, auto y) { return std::hypot(x, y); };
  auto l = eve::Valmax<EVE_TYPE>();
  EVE_REGISTER_BENCHMARK(std_hypot2, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(-l, l)
                        , eve::bench::random<EVE_TYPE>(-l, l));
  auto const std_hypot3 = [](auto x, auto y, auto z) { return std::hypot(x, y, z); };
   EVE_REGISTER_BENCHMARK(std_hypot3, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(-l, l)
                        , eve::bench::random<EVE_TYPE>(-l, l)
                        , eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
