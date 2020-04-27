//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check ceil return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::ceil(T()), T);
}

TTS_CASE_TPL("Check eve::ceil behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::ceil(T(0)), T(0));
  TTS_EQUAL(eve::ceil(T(1)), T(1));
  TTS_EQUAL(eve::ceil(T(2)), T(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::ceil(T(-1)), T(-1));
    TTS_EQUAL(eve::ceil(T(-2)), T(-2));
  }
  else if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::ceil(T(-1.3)), T(-1));
   TTS_EQUAL(eve::ceil(T(-1.5)), T(-1));
   TTS_EQUAL(eve::ceil(T(-1.6)), T(-1));
   TTS_EQUAL(eve::ceil(T(1.3)) , T(2));
   TTS_EQUAL(eve::ceil(T(1.5)) , T(2));
   TTS_EQUAL(eve::ceil(T(1.6)) , T(2));
  }
}
