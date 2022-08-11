//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>

int main()
{
  EVE_REGISTER_BENCHMARK(eve::two_split, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

}
