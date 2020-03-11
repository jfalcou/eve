//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log2.hpp>
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

TTS_CASE("Check eve::plain_(eve::log2) return type")
{
  TTS_EXPR_IS(eve::plain_(eve::log2)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE(" log2")
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::plain_(eve::log2)(eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log2)(eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log2)(eve::Mone<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log2)(eve::Zero<EVE_TYPE>()), eve::Minf<EVE_TYPE>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::plain_(eve::log2)(eve::Mindenormal<EVE_TYPE>()), EVE_TYPE(std::log2(eve::Mindenormal<EVE_VALUE>())), 0);
  }
  
  TTS_ULP_EQUAL(eve::plain_(eve::log2)(eve::One<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::plain_(eve::log2)(EVE_TYPE(2)), EVE_TYPE(1), 0);
  TTS_ULP_EQUAL(eve::plain_(eve::log2)(EVE_TYPE(8)), EVE_TYPE(3), 0);
  TTS_ULP_EQUAL(eve::plain_(eve::log2)(EVE_TYPE(64)), EVE_TYPE(6), 0);
}
