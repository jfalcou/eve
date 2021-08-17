//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <numbers>
#include <cmath>

int main(int argc, char** argv)
{
  constexpr EVE_TYPE invpi = std::numbers::inv_pi_v<EVE_TYPE>;
  auto const std_acscpi = [invpi](auto x) { return invpi*std::asin(1/x); };
  EVE_REGISTER_BENCHMARK(std_acscpi, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(EVE_TYPE(1), eve::valmax(eve::as<EVE_TYPE>())));

  eve::bench::start_benchmarks(argc, argv);
}
