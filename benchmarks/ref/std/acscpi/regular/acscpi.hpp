//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <numbers>
#include <cmath>

int main(int argc, char** argv)
{
  using EVE_TYPE = eve::detail::value_type_t<EVE_TYPE>;
  constexpr EVE_TYPE invpi = std::numbers::inv_pi_v<EVE_TYPE>;
  auto const std_acscpi = [invpi](auto x) { return invpi*std::asin(1/x); };
  EVE_REGISTER_BENCHMARK(std_acscpi, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(EVE_TYPE(1), eve::Valmax<EVE_TYPE>()));

  eve::bench::start_benchmarks(argc, argv);
}
