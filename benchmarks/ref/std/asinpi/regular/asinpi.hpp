//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <numbers>
#include <cmath>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>

int main(int argc, char** argv)
{
  constexpr EVE_TYPE invpi = std::numbers::inv_pi_v<EVE_TYPE>;
  auto const std_asinpi = [invpi](auto x) { return invpi*std::asin(x); };
  EVE_REGISTER_BENCHMARK(std_asinpi, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(EVE_TYPE(1), eve::Valmax<EVE_TYPE>()));

  eve::bench::start_benchmarks(argc, argv);
}
