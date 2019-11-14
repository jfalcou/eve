//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanh.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::tanh return type")
{
  TTS_EXPR_IS(eve::tanh(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::tanh behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::tanh(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::tanh(eve::Inf<Type>()) , (Type(1)) );
    TTS_IEEE_EQUAL(eve::tanh(eve::Minf<Type>()), (Type(-1)) );   
  }
  TTS_ULP_EQUAL(eve::tanh(Type(1)), Type(std::tanh(Value(1))), 0.5);
  TTS_ULP_EQUAL(eve::tanh(Type(-1)),Type(std::tanh(Value(-1))), 0.5); 
  TTS_IEEE_EQUAL((eve::tanh(Type(0))), (eve::Zero<Type>()));
  TTS_IEEE_EQUAL((eve::tanh(eve::Mzero<Type>())), (eve::Zero<Type>()));
  TTS_EXPECT(eve::all(eve::is_negative(eve::tanh(eve::Mzero<Type>()))) );
  TTS_EXPECT(eve::all(eve::is_positive(eve::tanh(Type(0))))            );
}
