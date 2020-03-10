//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/function/cos.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted_(eve::sinpi) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::sinpi)(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::sinpi behavior")
{
 
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_EXPECT(eve::all(eve::is_positive(eve::restricted_(eve::sinpi)(eve::Zero<Type>()))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::restricted_(eve::sinpi)(eve::Mzero<Type>()))));    
  TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(Type(0)), (Type(0)));
  TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(eve::Mzero<Type>()), (Type(0)));
  TTS_ULP_EQUAL((eve::restricted_(eve::sinpi)(Type(0.125))), (Type(0.38268343236508977172845998403039886676134456248563)), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::sinpi)(-Type(0.125))),(Type(-0.38268343236508977172845998403039886676134456248563)), 0.5);
}
