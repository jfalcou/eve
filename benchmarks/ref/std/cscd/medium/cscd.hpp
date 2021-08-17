//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <numbers>

int main(int argc, char** argv)
{
  constexpr EVE_TYPE inrad = std::numbers::pi_v<EVE_TYPE>/180;
  auto const std_cscd = [](auto x) { return inrad*1/std::sin(x); };

  auto l = eve::detail::Rempio2_limit(eve::medium_type(),eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_cscd, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
