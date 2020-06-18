//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <cmath>

int main()
{
  using EVE_VALUE = eve::detail::value_type_t<EVE_TYPE>;
  auto lmax = eve::detail::Rempio2_limit(eve::medium_type(), eve::as_<EVE_VALUE>());
  auto lmin = -lmax;
  EVE_REGISTER_BENCHMARK(eve::medium_(eve::csc), EVE_TYPE
                        , eve::bench::random<EVE_TYPE>(lmin,lmax));

}
