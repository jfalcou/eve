//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/all.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  EVE_VALUE lmax = eve::cardinal_v<EVE_TYPE>+1;
  EVE_VALUE lmin = -lmax;
  if (lmin > 0) lmin = 0;
  EVE_REGISTER_BENCHMARK(eve::all, EVE_TYPE, eve::bench::random<EVE_TYPE>(lmin, lmax));

  using L_TYPE = eve::logical<EVE_TYPE>;
  EVE_REGISTER_BENCHMARK(eve::all, L_TYPE, eve::bench::random<L_TYPE>(0, 1));

}
