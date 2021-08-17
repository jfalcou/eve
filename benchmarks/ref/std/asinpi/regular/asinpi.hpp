//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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
                        , eve::bench::random<EVE_TYPE>(EVE_TYPE(1), eve::valmax(eve::as<EVE_TYPE>())));

  eve::bench::start_benchmarks(argc, argv);
}
