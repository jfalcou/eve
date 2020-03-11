//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/constant/pio_2.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::small_(eve::sin) return type")
{
  TTS_EXPR_IS(eve::small_(eve::sin)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::small_(eve::sin) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::small_(eve::sin)(EVE_TYPE(1)),  EVE_TYPE(std::sin(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)(EVE_TYPE(-1)), EVE_TYPE(std::sin(-1.0)), 0.5); 
  TTS_IEEE_EQUAL((eve::small_(eve::sin)(EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL((eve::small_(eve::sin)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::small_(eve::sin)(eve::Mzero<EVE_TYPE>()))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::small_(eve::sin)(eve::Zero<EVE_TYPE>()))));
  TTS_ULP_EQUAL((eve::small_(eve::sin)(eve::Pio_2<EVE_TYPE>())), (EVE_TYPE(std::sin(eve::Pio_2<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(-eve::Pio_2<EVE_TYPE>())),(EVE_TYPE(std::sin(-eve::Pio_2<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(std::sin(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(std::sin(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(eve::Pio_4<EVE_TYPE>()/2)), (EVE_TYPE(std::sin(eve::Pio_4<EVE_VALUE>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(-eve::Pio_4<EVE_TYPE>()/2)),(EVE_TYPE(std::sin(-eve::Pio_4<EVE_VALUE>()/2))), 0.5); 
}
