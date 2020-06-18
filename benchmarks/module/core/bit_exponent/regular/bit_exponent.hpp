//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_exponent.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmin = eve::Maxlog<EVE_VALUE>();
  auto lmax = eve::Minlog<EVE_VALUE>();
   EVE_REGISTER_BENCHMARK(eve::bit_exponent, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

}
