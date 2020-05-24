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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <cmath>

int main(int argc, char** argv)
{
  auto const std_tan = [](auto x) { return std::tan(x); };

  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::Pio_4<EVE_TYPE>(), eve::Pio_4<EVE_TYPE>()));
  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::Pio_2<EVE_TYPE>(), eve::Pio_2<EVE_TYPE>()));
  auto l = eve::detail::Rempio2_limit(eve::medium_type(),eve::as_<EVE_TYPE>());
  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(-l, l));
  EVE_REGISTER_BENCHMARK(std_tan, EVE_TYPE, eve::bench::random<EVE_TYPE>(eve::Valmin<EVE_TYPE>(), eve::Valmax<EVE_TYPE>()));

  eve::bench::start_benchmarks(argc, argv);
}
