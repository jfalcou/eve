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
  auto const std_sech = [](auto x) { return 1/std::cosh(x); };
  auto l = eve::valmax(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_sech, EVE_TYPE
                        , eve::bench::random< EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
