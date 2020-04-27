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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check sincos return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::medium_(eve::sincos)(T()), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check (eve::sincos behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto pi_v = eve::Pi<v_t>();

  v_t x[]  = {  pi_v/8, -pi_v/8, pi_v/4, -pi_v/4, v_t(1), v_t(-1)
              , v_t(10), v_t(-10), v_t(1000000), v_t(-1000000)
              };

  for(auto v : x)
  {
    auto [p0, p1] = eve::medium_(eve::sincos)(T(v));
    TTS_ULP_EQUAL(p0, T(std::sin(v)), 0.5);
    TTS_ULP_EQUAL(p1, T(std::cos(v)), 0.5);
  }
}
