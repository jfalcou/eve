//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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

TTS_CASE("Check eve::musl_(eve::log1p) return type")
{
  TTS_EXPR_IS(eve::musl_(eve::log1p)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE(" log1p")
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Mone<EVE_TYPE>()), eve::Minf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Zero<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Mindenormal<EVE_TYPE>()), EVE_TYPE(std::log1p(eve::Mindenormal<EVE_VALUE>())), 0);
  }
  
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Eps<EVE_TYPE>()), eve::Eps<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Eps<EVE_TYPE>()), eve::Eps<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::One<EVE_TYPE>()), eve::Log_2<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Zero<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Smallestposval<EVE_TYPE>()), eve::Smallestposval<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::musl_(eve::log1p)(eve::Eps<EVE_TYPE>()), eve::Eps<EVE_TYPE>(), 0.5);
}
