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
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::medium_(eve::sin) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::medium_(eve::sin)(T()), T);
}

TTS_CASE_TPL("Check eve::medium_(eve::sin) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::sin)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sin)(eve::Inf<T>()) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sin)(eve::Minf<T>()), (eve::nan(eve::as<T>())) );
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::sin)(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::sin)(T( 0 )))));

  TTS_IEEE_EQUAL(eve::medium_(eve::sin)(T( 0 )), T(0));
  TTS_IEEE_EQUAL(eve::medium_(eve::sin)(T(-0.)), T(0));

  TTS_ULP_EQUAL(eve::medium_(eve::sin)(eve::Pio_4<T>()) , T(std::sin(eve::Pio_4<v_t>()))  , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)(-eve::Pio_4<T>()), T(std::sin(-eve::Pio_4<v_t>())) , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)( T( 1))          , T(std::sin(1.0))                , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)(-T( 1))          , T(std::sin(-1.0))               , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)( T(100.0))       , T(std::sin(v_t(100.0)))         , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)(-T(100.0))       , T(std::sin(v_t(-100.0)))        , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)( T(100000.0))    , T(std::sin(v_t(100000.0)))      , 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sin)(-T(100000.0))    , T(std::sin(v_t(-100000.0)))     , 0.5);
}
