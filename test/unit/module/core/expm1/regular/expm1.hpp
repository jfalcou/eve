//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expm1.hpp>
#include <eve/function/all.hpp>
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

TTS_CASE("Check eve::expm1 return type")
{
  TTS_EXPR_IS(eve::expm1(Type(0)), (Type));
}

TTS_CASE("Check eve::expm1 behavior")
{
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::expm1(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::expm1(eve::Inf<Type>()) , (eve::Inf<Type>()) );
    TTS_IEEE_EQUAL(eve::expm1(eve::Minf<Type>()), (Type(-1)) ); 
  }
  TTS_ULP_EQUAL(eve::expm1(Type(1)), Type(std::expm1(Value(1))), 0.5);
  TTS_ULP_EQUAL(eve::expm1(Type(-1)),Type(std::expm1(Value(-1))), 0.5); 
  TTS_IEEE_EQUAL((eve::expm1(Type(0))), (Type(0)));
  TTS_IEEE_EQUAL((eve::expm1(eve::Mzero<Type>())), (Type(0)));
  TTS_EXPECT(eve::all(eve::is_positive(eve::expm1((Type(0)))))          );
  TTS_EXPECT(eve::all(eve::is_negative(eve::expm1(eve::Mzero<Type>()))) );
}
