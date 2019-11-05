//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <cmath>

TTS_CASE("Check eve::exp return type")
{
  TTS_EXPR_IS(eve::exp(Type(0)), (Type));
}

TTS_CASE("Check eve::exp behavior")
{
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::exp(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::Inf<Type>()) , (eve::Inf<Type>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::Minf<Type>()), (eve::Zero<Type>()) ); 
  }
  TTS_ULP_EQUAL(eve::exp(Type(1)), Type(std::exp(Value(1))), 0.5);
  TTS_ULP_EQUAL(eve::exp(Type(-1)),Type(std::exp(Value(-1))), 0.5); 
  TTS_IEEE_EQUAL((eve::exp(Type(0))), (Type(1)));
  TTS_IEEE_EQUAL((eve::exp(eve::Mzero<Type>())), (Type(1)));
  }
