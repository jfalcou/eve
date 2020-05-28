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
#include <eve/detail/meta/traits.hpp>

int main(int argc, char** argv)
{
  using I_TYPE =  eve::detail::as_integer_t<EVE_TYPE>;
  auto const std_inearest = [](auto x) { return static_cast<I_TYPE>(std::nearbyint(x)); };
  auto lmax = eve::Valmax<EVE_TYPE>();
  auto lmin = eve::Valmin<EVE_TYPE>();
  EVE_REGISTER_BENCHMARK(std_inearest, EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin, lmax));

  eve::bench::start_benchmarks(argc, argv);
}
