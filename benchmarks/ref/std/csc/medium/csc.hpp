//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_csc = [](auto x) { return 1/std::sin(x); };
  auto l = eve::detail::Rempio2_limit(eve::medium_type(),eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_csc, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));

  eve::bench::start_benchmarks(argc, argv);
}
