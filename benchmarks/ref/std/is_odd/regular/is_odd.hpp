//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <cmath>
#include <type_traits>

int main(int argc, char** argv)
{
  if constexpr(std::is_integral_v<EVE_TYPE>)
  {
    auto const std_is_odd = [](auto x) { return static_cast<int>(x)&1; };
    EVE_REGISTER_BENCHMARK(std_is_odd, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

    eve::bench::start_benchmarks(argc, argv);
  }
  else
  {
    auto const std_is_odd = [](auto x) {x = x-1; return  (x/2-std::trunc(x/2)); };
    EVE_REGISTER_BENCHMARK(std_is_odd, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

    eve::bench::start_benchmarks(argc, argv);
  }
}
