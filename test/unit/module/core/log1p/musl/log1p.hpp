//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log1p.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::musl_(eve::log1p) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::musl_(eve::log1p)(T(0)), T);
}

TTS_CASE_TPL(" log1p", EVE_TYPE)
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Inf<T>()), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Nan<T>()), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Mone<T>()), eve::Minf<T>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(T( 0 )), T( 0 ), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Mindenormal<T>()), T(std::log1p(eve::Mindenormal<v_t>())), 0);
  }

  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Eps<T>()), eve::Eps<T>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Eps<T>()), eve::Eps<T>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::One<T>()), eve::Log_2<T>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(T( 0 )), T( 0 ), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Smallestposval<T>()), eve::Smallestposval<T>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Eps<T>()), eve::Eps<T>(), 0.5);
}
