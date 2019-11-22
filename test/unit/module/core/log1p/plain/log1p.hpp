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
#include <eve/constant/mone.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::musl_(eve::log1p) return type")
{
  TTS_EXPR_IS(eve::musl_(eve::log1p)(Type(0)), (Type));
}

TTS_CASE(" log1p")
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Nan<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Mone<Type>()), eve::Minf<Type>(), 0);
    TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Zero<Type>()), eve::Zero<Type>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Mindenormal<Type>()), Type(std::log1p(eve::Mindenormal<Value>())), 0);
  }
  
  TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Eps<Type>()), eve::Eps<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Eps<Type>()), eve::Eps<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::One<Type>()), eve::Log_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Zero<Type>()), eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Smallestposval<Type>()), eve::Smallestposval<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::plain_(eve::log1p)(eve::Eps<Type>()), eve::Eps<Type>(), 0.5);  
}
