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
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_sin = [](auto x) { return std::sin(x); };
  auto l = eve::detail::Rempio2_limit(eve::medium_type(),eve::as_<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_sin, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
