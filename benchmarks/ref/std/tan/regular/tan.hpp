//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_tan = [](auto x) { return std::tan(x); };

  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::pio_4(eve::as<EVE_TYPE>()), eve::pio_4(eve::as<EVE_TYPE>())));
  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::pio_2(eve::as<EVE_TYPE>()), eve::pio_2(eve::as<EVE_TYPE>())));
  auto l = eve::detail::Rempio2_limit(eve::medium_type(),eve::as<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));
  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::valmin(eve::as<EVE_TYPE>()), eve::valmax(eve::as<EVE_TYPE>())));

  eve::bench::start_benchmarks(argc, argv);
}
