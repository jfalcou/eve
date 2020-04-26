//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tand.hpp>
#include <eve/function/cos.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted_(eve::tand) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::tand)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::restricted_(eve::tand) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::tand)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::tand)(EVE_TYPE(90)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::tand)(EVE_TYPE(-90)),eve::Nan<EVE_TYPE>(), 0.5);
  TTS_IEEE_EQUAL((eve::restricted_(eve::tand)(EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL((eve::restricted_(eve::tand)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(0)));
  TTS_ULP_EQUAL((eve::restricted_(eve::tand)(EVE_TYPE(45))), (EVE_TYPE(std::tan(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::tand)(-EVE_TYPE(45))),(EVE_TYPE(std::tan(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  
}
