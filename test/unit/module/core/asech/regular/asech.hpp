//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asech.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::asech return type")
{
  TTS_EXPR_IS(eve::asech(Type(0)), (Type));
}

TTS_CASE("Check eve::asech behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asech(eve::Nan<Type>()) , eve::Nan<Type>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asech(eve::Inf<Type>()) , eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asech(eve::Minf<Type>()) , eve::Nan<Type>(), 0);   
  }

  TTS_ULP_EQUAL(eve::asech(Type( 2))         ,  eve::Nan<Type>()  , 0   );
  TTS_ULP_EQUAL(eve::asech(Type(-2))         ,  eve::Nan<Type>()  , 0   );
  TTS_ULP_EQUAL(eve::asech(Type( 1. ))       ,  eve::Zero<Type>() , 0   );
  TTS_ULP_EQUAL(eve::asech(Type( 0.5 ))     ,  Type(std::acosh(Value(2))), 0.5  );
}
