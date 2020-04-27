//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
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

TTS_CASE_TPL("Check eve::restricted_(eve::cos) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::cos)(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::restricted_(eve::cos) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cos)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cos)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cos)(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::cos)(T(1)), eve::Nan<T>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::cos)(T(-1)),eve::Nan<T>(), 0.5);
  TTS_IEEE_EQUAL((eve::restricted_(eve::cos)(T(0))), (T(1)));
  TTS_IEEE_EQUAL((eve::restricted_(eve::cos)(T(-0.))), (T(1)));
  TTS_ULP_EQUAL((eve::restricted_(eve::cos)(eve::Pio_4<T>())), (T(std::cos(eve::Pio_4<v_t>()))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cos)(-eve::Pio_4<T>())),(T(std::cos(-eve::Pio_4<v_t>()))), 0.5);

}
