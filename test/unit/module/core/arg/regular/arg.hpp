//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/arg.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::arg return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::arg(T(0)), T);
}

TTS_CASE_TPL("Check eve::arg behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_EQUAL( eve::arg(eve::inf(eve::as<T>()))  , T( 0 )       );
    TTS_EQUAL( eve::arg(eve::Minf<T>()) , eve::Pi<T>() );
  }

  TTS_EQUAL( eve::arg(T(-1 )), eve::Pi<T>() );
  TTS_EQUAL( eve::arg(T(-0.)), eve::Pi<T>() );
  TTS_EQUAL( eve::arg(T( 0 )), T( 0 ) );
  TTS_EQUAL( eve::arg(T( 1 )), T( 0 ) );
}
