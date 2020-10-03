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
#include <eve/constant/nan.hpp>
#include <type_traits>
#include <tuple>
#include <cmath>

TTS_CASE("Check eve::restricted(eve::sincos) return type")
{
  TTS_EXPR_IS(eve::restricted(eve::sincos)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check eve::restricted(eve::sincos) behavior")
{
  static const int N = 6;
  EVE_VALUE x[N]  = { EVE_VALUE(1)/8, -EVE_VALUE(1)/8, EVE_VALUE(1)/4, -EVE_VALUE(1)/4, EVE_VALUE(1), EVE_VALUE(-1) };

  for(int i=0; i < 4 ; ++i)
  {
    auto [p0, p1] = eve::restricted(eve::sincos)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, EVE_TYPE(std::sin(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, EVE_TYPE(std::cos(x[i])), 0.5);
  }

  for(int i=4; i < 6 ; ++i)
  {
    auto [p0, p1] = eve::restricted(eve::sincos)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, eve::nan(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(p1, eve::nan(eve::as<EVE_TYPE>()), 0.5);
  }
}
