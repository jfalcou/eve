//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::medium_(eve::sin) return type")
{
  TTS_EXPR_IS(eve::medium_(eve::sin)(Type(0)), (Type));
}

TTS_CASE("Check eve::medium_(eve::sin) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::sin)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sin)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sin)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::sin)(Type(1)), Type(std::sin(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)(Type(-1)),Type(std::sin(-1.0)), 0.5);
  TTS_IEEE_EQUAL((eve::medium_(eve::sin)(Type(0))), (Type(0)));
  TTS_IEEE_EQUAL((eve::medium_(eve::sin)(eve::Mzero<Type>())), (Type(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::sin)(eve::Mzero<Type>()))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::sin)(eve::Zero<Type>()))));
  TTS_ULP_EQUAL((eve::medium_(eve::sin)(eve::Pio_4<Type>())), (Type(std::sin(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sin)(-eve::Pio_4<Type>())),(Type(std::sin(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sin)(Type(100.0))), Type(std::sin(Value(100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sin)(Type(-100.0))),Type(std::sin(Value(-100.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sin)(Type(100000.0))), Type(std::sin(Value(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sin)(Type(-100000.0))),Type(std::sin(Value(-100000.0))), 0.5);
}

