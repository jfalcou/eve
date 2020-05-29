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

int main(int argc, char** argv)
{
  using EVE_TYPE = eve::detail::value_type_t<EVE_TYPE>;
  auto const std_pow = [](auto x, auto y) { return std::pow(x, y); };
  auto lmin = EVE_TYPE(-10);
  auto lmax = EVE_TYPE(10);
  EVE_REGISTER_BENCHMARK(std_pow, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
