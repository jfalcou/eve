//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <cmath>

TTS_CASE("Check sincos return type")
{
  TTS_EXPR_IS((eve::sincos(EVE_TYPE())), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check (eve::sincos behavior")
{
  auto pi_v   = eve::pi(eve::as<EVE_VALUE>());
  auto max_v  = eve::valmax(eve::as<EVE_VALUE>());
  auto min_v  = eve::valmin(eve::as<EVE_VALUE>());

  EVE_VALUE x[] = { pi_v/8, -pi_v/8, pi_v/4, -pi_v/4, EVE_VALUE(1), EVE_VALUE(-1), EVE_VALUE(10), EVE_VALUE(-10)
            , EVE_VALUE(1000000), EVE_VALUE(-1000000), EVE_VALUE(1000000000), EVE_VALUE(-1000000000)
            , max_v, min_v, max_v/100000, min_v/100000
            };

  for(auto v : x)
  {
    auto [p0, p1] = eve::sincos(EVE_TYPE(v));
    TTS_ULP_EQUAL(p0, EVE_TYPE(std::sin(v)), 0.5);
    TTS_ULP_EQUAL(p1, EVE_TYPE(std::cos(v)), 0.5);
  }
}
