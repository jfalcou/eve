//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/min.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::min return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::min(T(0)  , T(0) ) , T);
  TTS_EXPR_IS(eve::min(v_t(0) , T(0) ) , T);
  TTS_EXPR_IS(eve::min(T(0)  , v_t(0)) , T);
}

TTS_CASE_TPL("Check eve::min behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::min((T(0)), (T(0))), (T(0)));
  TTS_EQUAL(eve::min((T(0)), (T(1))), (T(0)));
  TTS_EQUAL(eve::min((T(1)), (T(0))), (T(0)));
  TTS_EQUAL(eve::min((T(1)), (T(1))), (T(1)));

  TTS_EQUAL(eve::min((v_t(0)), (T(0))), (T(0)));
  TTS_EQUAL(eve::min((v_t(0)), (T(1))), (T(0)));
  TTS_EQUAL(eve::min((v_t(1)), (T(0))), (T(0)));
  TTS_EQUAL(eve::min((v_t(1)), (T(1))), (T(1)));

  TTS_EQUAL(eve::min((T(0)), (v_t(0))), (T(0)));
  TTS_EQUAL(eve::min((T(0)), (v_t(1))), (T(0)));
  TTS_EQUAL(eve::min((T(1)), (v_t(0))), (T(0)));
  TTS_EQUAL(eve::min((T(1)), (v_t(1))), (T(1)));
}
