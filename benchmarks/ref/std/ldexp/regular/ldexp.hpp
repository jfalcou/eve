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
  auto const std_ldexp = [](auto x, int y) { return std::ldexp(x, y); };
  auto l = eve::valmax(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_ldexp, EVE_TYPE
                        , eve::bench::random< EVE_TYPE>(-l, l)
                        , eve::bench::random< int>(-100, 100));

  eve::bench::start_benchmarks(argc, argv);
}
