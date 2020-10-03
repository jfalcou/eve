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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <tuple>
#include <cmath>

TTS_CASE("Check eve::small(eve::sincos) return type")
{
  TTS_EXPR_IS(eve::small(eve::sincos)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check eve::small(eve::sincos) behavior")
{
  auto pi_v = eve::pi(eve::as<EVE_VALUE>());

  EVE_VALUE x[] = {  pi_v/8, -pi_v/8, pi_v/4, -pi_v/4, 3*pi_v/8, -3*pi_v/8
            , eve::pio_2(eve::as<EVE_VALUE>()), -pi_v/2, EVE_VALUE(1.57079632679489655800e+00)
            };

  for(auto v :x)
  {
    auto [p0, p1] = eve::small(eve::sincos)(EVE_TYPE(v));
    TTS_ULP_EQUAL(p0, EVE_TYPE(std::sin(v)), 3.5);
    TTS_ULP_EQUAL(p1, EVE_TYPE(std::cos(v)), 3.5);
  }
}
