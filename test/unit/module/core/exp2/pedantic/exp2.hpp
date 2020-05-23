//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::pedantic_(eve::exp2) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::exp2)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::exp2) behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL (eve::pedantic_(eve::exp2)(T(1)), T(2), 0.5);
  TTS_IEEE_EQUAL(eve::pedantic_(eve::exp2)(T(0)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::pedantic_(eve::exp2)(eve::Nan<T>()) , eve::Nan<T>() );
      TTS_IEEE_EQUAL(eve::pedantic_(eve::exp2)(eve::Inf<T>()) , eve::Inf<T>() );
      TTS_IEEE_EQUAL(eve::pedantic_(eve::exp2)(eve::Minf<T>()), T( 0 ) );
    }

    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp2)(T(-0.)), T(1));
    TTS_ULP_EQUAL (eve::pedantic_(eve::exp2)(T(-1)) , T(0.5), 0.5);
  }
}
