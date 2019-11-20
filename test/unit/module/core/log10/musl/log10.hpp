//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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

TTS_CASE("Check eve::musl_(eve::log10) return type")
{
  TTS_EXPR_IS(eve::musl_(eve::log10)(Type(0)), (Type));
}

TTS_CASE_TPL (" log10",  TTS_IEEE_TYPES)
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Nan<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Mone<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Zero<Type>()), eve::Minf<Type>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::Mindenormal<Type>()), Type(std::log10(eve::Mindenormal<Value>())), 0);
  }
  
  TTS_ULP_EQUAL(eve::musl_(eve::log10)(eve::One<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::musl_(eve::log10)(Type(10)), Type(1), 0);
  TTS_ULP_EQUAL(eve::musl_(eve::log10)(Type(1000)), Type(3), 0);
  TTS_ULP_EQUAL(eve::musl_(eve::log10)(Type(1000000)), Type(6), 0);
}
