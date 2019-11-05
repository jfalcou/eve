//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/coth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::coth return type")
{
  TTS_EXPR_IS(eve::coth(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::coth behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::coth(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::coth(eve::Inf<Type>()) , (Type(1)) );
    TTS_IEEE_EQUAL(eve::coth(eve::Minf<Type>()), (Type(-1)) );   
  }
  TTS_ULP_EQUAL(eve::coth(Type(1)), Type(eve::rec(std::tanh(Type(1))), 0.5);
  TTS_ULP_EQUAL(eve::coth(Type(-1)),Type(eve::rec(std::tanh(Type(-1))), 0.5); 
  TTS_IEEE_EQUAL((eve::coth(Type(0))), (eve::Inf<Type>()));
  TTS_IEEE_EQUAL((eve::coth(eve::Mzero<Type>())), (eve::Minf<Type>()));

}
