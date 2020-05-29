//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <numeric>

int main(int argc, char** argv)
{
  using EVE_TYPE = eve::detail::value_type_t<EVE_TYPE>;
  auto const std_min = [](auto x, auto y) { return std::min(x, y); };
  auto lmin = eve::Valmin<EVE_TYPE>();
  auto lmax = eve::Valmax<EVE_TYPE>();
  EVE_REGISTER_BENCHMARK(std_min, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax)
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

  eve::bench::start_benchmarks(argc, argv);
}
