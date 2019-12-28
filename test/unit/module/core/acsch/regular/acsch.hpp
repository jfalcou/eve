//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acsch.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::acsch return type")
{
  TTS_EXPR_IS(eve::acsch(Type(0)), (Type));
}

TTS_CASE("Check eve::acsch behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acsch(eve::Nan<Type>()) , eve::Nan<Type>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acsch(eve::Inf<Type>()) , Type(0), 0);
    TTS_ULP_EQUAL(eve::acsch(eve::Minf<Type>()) , Type(-0.0), 0);
    TTS_EXPECT(eve::all(eve::is_negative(eve::acsch(eve::Minf<Type>()))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::acsch(eve::Inf<Type>()))));   
  }

  TTS_ULP_EQUAL(eve::acsch(Type( 0.5)) , Type(std::asinh(Value(2.)))  , 0   );
  TTS_ULP_EQUAL(eve::acsch(Type(-0.5)) , Type(std::asinh(Value(-2.)))  , 0   );
  TTS_ULP_EQUAL(eve::acsch(Type( 1. )) , Type(std::asinh(Value(1.0)))  , 0.5   );
  TTS_ULP_EQUAL(eve::acsch(Type( 2. )) , Type(std::asinh(Value(0.5))), 0.5  );
}
