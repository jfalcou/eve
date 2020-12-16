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
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <numbers>

int main(int argc, char** argv)
{
  auto const std_secpi = [](auto x) { return 1/std::cos(std::numbers::pi_v<EVE_TYPE>*x); };
  auto l = eve::detail::Rempio2_limit(eve::medium_type(),eve::as_<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_secpi, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
