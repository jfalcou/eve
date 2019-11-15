//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinh.hpp>
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

TTS_CASE("Check eve::sinh return type")
{
  TTS_EXPR_IS(eve::sinh(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::sinh behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sinh(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::sinh(eve::Inf<Type>()) , (eve::Inf<Type>()) );
    TTS_IEEE_EQUAL(eve::sinh(eve::Minf<Type>()), (eve::Minf<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::sinh(Type(1)), Type(std::sinh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::sinh(Type(-1)),Type(std::sinh(-1.0)), 0.5);
  TTS_IEEE_EQUAL((eve::sinh(Type(0))), (Type(0)));
  TTS_IEEE_EQUAL((eve::sinh(eve::Mzero<Type>())), (Type(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::sinh(eve::Mzero<Type>()))) );
  TTS_EXPECT(eve::all(eve::is_positive(eve::sinh(Type(0))))            );

}
