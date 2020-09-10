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
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::pedantic_(eve::exp) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::exp)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::exp) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::inf(eve::as<T>())) , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::minf(eve::as<T>())), T( 0 ) );
  }

  TTS_ULP_EQUAL(eve::pedantic_(eve::exp)(T(1)), T(std::exp(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::exp)(T(-1)),T(std::exp(v_t(-1))), 0.5);

  TTS_IEEE_EQUAL( eve::pedantic_(eve::exp)(T( 0.)), T(1));
  TTS_IEEE_EQUAL( eve::pedantic_(eve::exp)(T(-0.)), T(1));
  v_t z = eve::Minlog<v_t>()+1;
  TTS_ULP_EQUAL( eve::pedantic_(eve::exp)(T(z)), T(std::exp((z))), 0.5);
}
