//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  using EVE_TYPE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmin = eve::Maxlog<EVE_TYPE>();
  auto lmax = eve::Minlog<EVE_TYPE>();
  auto const std_fdim = [](auto x, auto y) { return std::fdim(x, y); };

  EVE_REGISTER_BENCHMARK(std_fdim, EVE_TYPE
                         , eve::bench::random<EVE_TYPE>(lmin, lmax)
                         , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
