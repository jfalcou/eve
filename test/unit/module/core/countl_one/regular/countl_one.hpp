//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/countl_one.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check countl_one return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::countl_one(T()), T);
}

TTS_CASE_TPL("Check eve::countl_one behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::countl_one(T(~0)), T(sizeof(v_t) * 8     ));
  TTS_EQUAL(eve::countl_one(T(~2)), T(sizeof(v_t) * 8 - 2 ));
  TTS_EQUAL(eve::countl_one(T(~5)), T(sizeof(v_t) * 8 - 3 ));
  TTS_EQUAL(eve::countl_one(T(~6)), T(sizeof(v_t) * 8 - 3 ));
  TTS_EQUAL(eve::countl_one(T(~9)), T(sizeof(v_t) * 8 - 4 ));
}
