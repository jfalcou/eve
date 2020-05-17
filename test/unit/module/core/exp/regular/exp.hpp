//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::exp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exp(T(0)), T);
}

TTS_CASE_TPL("Check eve::exp behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::exp(eve::Nan<T>()) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::exp(eve::Inf<T>()) , eve::Inf<T>() );
    TTS_IEEE_EQUAL(eve::exp(eve::Minf<T>()), T( 0 ) );
  }

  TTS_ULP_EQUAL(eve::exp(T(1)), T(std::exp(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::exp(T(-1)),T(std::exp(v_t(-1))), 0.5);

  TTS_IEEE_EQUAL( eve::exp(T( 0.)), T(1));
  TTS_IEEE_EQUAL( eve::exp(T(-0.)), T(1));
}
