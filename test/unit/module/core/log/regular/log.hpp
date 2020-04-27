//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::log return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::log(T(0)), T);
}

TTS_CASE_TPL(" log", EVE_TYPE)
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::log(eve::Inf<T>()), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::log(eve::Nan<T>()), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::log(eve::Mone<T>()), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::log(T( 0 )), eve::Minf<T>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::log(eve::Mindenormal<T>()), T(std::log(eve::Mindenormal<v_t>())), 0);
  }

  TTS_ULP_EQUAL(eve::log(eve::One<T>()), T( 0 ), 0);
  TTS_ULP_EQUAL(eve::log(T(2)), T(std::log(v_t(2))), 0);
  TTS_ULP_EQUAL(eve::log(T(8)), T(std::log(v_t(8))), 0);
  TTS_ULP_EQUAL(eve::log(T(64)), T(std::log(v_t(64))), 0);
}
