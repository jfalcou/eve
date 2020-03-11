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

TTS_CASE("Check eve::plain_(eve::log) return type")
{
  TTS_EXPR_IS(eve::plain_(eve::log)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE (" log")
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::plain_(eve::log)(eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log)(eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log)(eve::Mone<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log)(eve::Zero<EVE_TYPE>()), eve::Minf<EVE_TYPE>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::plain_(eve::log)(eve::Mindenormal<EVE_TYPE>()), EVE_TYPE(std::log(eve::Mindenormal<EVE_VALUE>())), 0);
  }
  
  TTS_ULP_EQUAL(eve::plain_(eve::log)(eve::One<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::plain_(eve::log)(EVE_TYPE(2)), EVE_TYPE(std::log(EVE_VALUE(2))), 0);
  TTS_ULP_EQUAL(eve::plain_(eve::log)(EVE_TYPE(8)), EVE_TYPE(std::log(EVE_VALUE(8))), 0);
  TTS_ULP_EQUAL(eve::plain_(eve::log)(EVE_TYPE(64)), EVE_TYPE(std::log(EVE_VALUE(64))), 0);
  TTS_ULP_EQUAL(eve::plain_(eve::log)(EVE_TYPE(2.118033886)), EVE_TYPE(std::log(EVE_VALUE(2.118033886))), 0);
}
