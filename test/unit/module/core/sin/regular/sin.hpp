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
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sin return type")
{
  TTS_EXPR_IS(eve::sin(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::sin behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sin(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::sin(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::sin(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::sin(EVE_TYPE(1)), EVE_TYPE(std::sin(EVE_VALUE(1.0))), 0.5);
  TTS_ULP_EQUAL(eve::sin(EVE_TYPE(-1.0)),EVE_TYPE(std::sin(EVE_VALUE(-1.0))), 0.5);
  TTS_IEEE_EQUAL((eve::sin(EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL((eve::sin(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(0)));
  TTS_ULP_EQUAL((eve::sin(eve::Pio_4<EVE_TYPE>())), (EVE_TYPE(std::sin(eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL((eve::sin(-eve::Pio_4<EVE_TYPE>())),(EVE_TYPE(std::sin(-eve::Pio_4<EVE_VALUE>()))), 0.5);
  TTS_ULP_EQUAL(eve::sin(EVE_TYPE(100000.0)), EVE_TYPE(std::sin(100000.0)), 0.5);
  TTS_ULP_EQUAL(eve::sin(EVE_TYPE(-100000.0)),EVE_TYPE(std::sin(-100000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::sin)(EVE_TYPE(-100000000.0))),EVE_TYPE(std::sin(-100000000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::sin)(EVE_TYPE(eve::Valmax<EVE_TYPE>()))),EVE_TYPE(std::sin(eve::Valmax<EVE_VALUE>())), 0.5);
}
