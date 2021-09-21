//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/two_split.hpp>
#include <cmath>

int main()
{
  EVE_REGISTER_BENCHMARK(eve::two_split, EVE_TYPE, eve::bench::random<EVE_TYPE>(-1.,1.));

}
