//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <cmath>
#include <eve/module/special.hpp>

int main()
{
  EVE_REGISTER_BENCHMARK(eve::signgam, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

}
