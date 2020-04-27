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
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::pedantic_(eve::exp) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::exp)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::exp) behavior", EVE_TYPE)
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::Inf<T>()) , (eve::Inf<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::exp)(eve::Minf<T>()), (T( 0 )) );
  }
  TTS_ULP_EQUAL(eve::pedantic_(eve::exp)(T(1)), T(std::exp(v_t(1))), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::exp)(T(-1)),T(std::exp(v_t(-1))), 0.5);
  TTS_IEEE_EQUAL((eve::pedantic_(eve::exp)(T(0))), (T(1)));
  TTS_IEEE_EQUAL((eve::pedantic_(eve::exp)(T(-0.))), (T(1)));
  }
