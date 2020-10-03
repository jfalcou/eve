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
#include <eve/constant/pi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/all.hpp>
#include <cmath>

TTS_CASE("Check  eve::big(eve::sincos) return type")
{
  TTS_EXPR_IS(eve::big(eve::sincos)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check  eve::big(eve::sincos) behavior")
{
  auto pi_v = eve::pi(eve::as<EVE_VALUE>());

  EVE_VALUE x[] = {  pi_v/8, -pi_v/8, pi_v/4, -pi_v/4, EVE_VALUE(1), EVE_VALUE(-1), EVE_VALUE(10), EVE_VALUE(-10)};

  for(int i=0; i < 8; ++i)
  {
    auto [p0, p1] = eve::big(eve::sincos)(EVE_TYPE(x[i]));
    EVE_VALUE pp0 = std::sin(x[i]);
    EVE_VALUE pp1 = std::cos(x[i]);
    TTS_ULP_EQUAL(p0, EVE_TYPE(pp0), 0.5);
    TTS_ULP_EQUAL(p1, EVE_TYPE(pp1), 0.5);
  }
}
