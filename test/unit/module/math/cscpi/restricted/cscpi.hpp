//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::restricted_(eve::cscpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::cscpi)(T()), T);
}

TTS_CASE_TPL("Check eve::restricted_(eve::cscpi) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cscpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cscpi)(eve::Inf<T>()) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cscpi)(eve::Minf<T>()), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted_(eve::cscpi)(T(0))     , eve::Inf<T>() );
  TTS_IEEE_EQUAL(eve::restricted_(eve::cscpi)(T(-0.))   , eve::Minf<T>());
  TTS_ULP_EQUAL(eve::restricted_(eve::cscpi)(T(0.125))  , T(2.6131259297527530557132863468543743071675223766986)  , 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::cscpi)(-T(0.125)) , T(-2.6131259297527530557132863468543743071675223766986) , 0.5);
}

