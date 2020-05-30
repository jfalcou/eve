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
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::sin return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sin(T()), T);
}

TTS_CASE_TPL("Check eve::sin behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sin(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::sin(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::sin(eve::Minf<T>()), (eve::Nan<T>()) );
  }

  TTS_IEEE_EQUAL(eve::sin(T(0))   , T(0));
  TTS_IEEE_EQUAL(eve::sin(T(-0.)) , T(0));

  TTS_ULP_EQUAL(eve::sin(T( 1))               , T(std::sin(v_t(1))) , 0.5);
  TTS_ULP_EQUAL(eve::sin(T(-1))               , T(std::sin(v_t(-1))), 0.5);
  TTS_ULP_EQUAL(eve::sin( eve::Pio_4<T>())    , T(std::sin(eve::Pio_4<v_t>()))  , 0.5);
  TTS_ULP_EQUAL(eve::sin(-eve::Pio_4<T>())    , T(std::sin(-eve::Pio_4<v_t>())) , 0.5);
  TTS_ULP_EQUAL(eve::sin( T(100000.0))        , T(std::sin(100000.0)) , 0.5);
  TTS_ULP_EQUAL(eve::sin(-T(100000.0))        , T(std::sin(-100000.0)), 0.5);
  TTS_ULP_EQUAL(eve::sin(T(-100000000.0))     , T(std::sin(-100000000.0))       , 0.5);
  TTS_ULP_EQUAL(eve::sin(T(eve::Valmax<T>())) , T(std::sin(eve::Valmax<v_t>())) , 0.5);
}
