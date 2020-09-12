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
  auto const std_div = [](auto c, auto x, auto y) { return c ? EVE_TYPE(x/y) : x; };
  auto lmin = eve::valmin(eve::as<EVE_TYPE>());
  auto lmax = eve::valmax(eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_div, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin, lmax)
                        , eve::bench::random<EVE_TYPE>(lmin, lmax)
                        , eve::bench::random<EVE_TYPE>(EVE_TYPE(1), lmax));

  eve::bench::start_benchmarks(argc, argv);
}
