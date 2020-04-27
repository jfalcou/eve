//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log10.hpp>
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

TTS_CASE_TPL("Check eve::musl_(eve::log10) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::musl_(eve::log10)(T(0)), T);
}

TTS_CASE_TPL(" log10", EVE_TYPE)
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Inf<T>()), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Nan<T>()), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Mone<T>()), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(T( 0 )), eve::Minf<T>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Mindenormal<T>()), T(std::log10(eve::Mindenormal<v_t>())), 0);
  }

  TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::One<T>()), T( 0 ), 0);
  TTS_ULP_EQUAL(eve::musl_(eve::log10)(T(10)), T(1), 0);
  TTS_ULP_EQUAL(eve::musl_(eve::log10)(T(1000)), T(3), 0);
  TTS_ULP_EQUAL(eve::musl_(eve::log10)(T(1000000)), T(6), 0);
}
