//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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

TTS_CASE("Check eve::log return type")
{
  TTS_EXPR_IS(eve::log(Type(0)), (Type));
}

TTS_CASE_TPL (" log",  TTS_IEEE_TYPES)
{

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::log(eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::log(eve::Nan<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::log(eve::Mone<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::log(eve::Zero<Type>()), eve::Minf<Type>(), 0);
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_ULP_EQUAL(eve::log(eve::Mindenormal<Type>()), Type(std::log(eve::Mindenormal<Value>())), 0);
  }
  
  TTS_ULP_EQUAL(eve::log(eve::One<Type>()), eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::log(Type(2)), Type(std::log(Value(2))), 0);
  TTS_ULP_EQUAL(eve::log(Type(8)), Type(std::log(Value(8))), 0);
  TTS_ULP_EQUAL(eve::log(Type(64)), Type(std::log(Value(64))), 0);
}
