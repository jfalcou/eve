//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::big(eve::sec) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big(eve::sec)(T()), T);
}

TTS_CASE_TPL("Check eve::big(eve::sec) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto ref_sec =  [](auto x){return eve::rec(std::cos(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::sec)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big(eve::sec)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big(eve::sec)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::big(eve::sec)(T( 0 )), T(ref_sec(0.0)) );
  TTS_IEEE_EQUAL(eve::big(eve::sec)(T(-0.)), T(ref_sec(0.0)) );

  TTS_ULP_EQUAL(eve::big(eve::sec)( T(1))                  , T(ref_sec(1.0))                   , 1.0 );
  TTS_ULP_EQUAL(eve::big(eve::sec)( T(-1))                 , T(ref_sec(-1.0))                  , 1.0 );
  TTS_ULP_EQUAL(eve::big(eve::sec)( eve::pio_4(eve::as<T>()))       , T(ref_sec(eve::pio_4(eve::as<v_t>())))     , 0.75);
  TTS_ULP_EQUAL(eve::big(eve::sec)(-eve::pio_4(eve::as<T>()))       , T(ref_sec(-eve::pio_4(eve::as<v_t>())))    , 0.75);
  TTS_ULP_EQUAL(eve::big(eve::sec)( T(100000.0))           , T(ref_sec(100000.0))              , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::sec)(-T(100000.0))           , T(ref_sec(-100000.0))             , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::sec)( T(100000000.0))        , T(ref_sec(100000000.0))           , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::sec)(-T(100000000.0))        , T(ref_sec(-100000000.0))          , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::sec)(T(eve::valmax(eve::as<T>())))    , T(ref_sec(eve::valmax(eve::as<v_t>())))    , 1.5 );
  TTS_ULP_EQUAL(eve::big(eve::sec)(T(eve::valmax(eve::as<T>()))/10) , T(ref_sec(eve::valmax(eve::as<v_t>())/10)) , 1.5 );
}
