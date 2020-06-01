//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::raw_(eve::pow) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw_(eve::pow)(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::raw_(eve::pow) behavior", EVE_TYPE)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0), T(-1)), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(0), T(-2)), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0), T(-2)), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0),  eve::Minf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(0),  eve::Minf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0.5), eve::Inf<T>()),  T( 0 ), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(2), eve::Inf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0.5), eve::Minf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(2), eve::Minf<T>()),  T( 0 ), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<T>(), T(4) ),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<T>(), T(-4) ),  T( 0 ), 0);
  }

  TTS_EQUAL(eve::raw_(eve::pow)(T(2),-3), T(1/8.0));
  TTS_EQUAL(eve::raw_(eve::pow)(T(2),3) , T(8)    );
  TTS_EQUAL(eve::raw_(eve::pow)(T(2),3u), T(8)    );
}
