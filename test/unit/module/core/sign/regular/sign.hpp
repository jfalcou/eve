//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sign.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::sign return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sign(T()), T);
}

TTS_CASE_TPL("Check eve::sign behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::sign(static_cast<T>(-2)), (T(-1)));
  }

  TTS_EQUAL(eve::sign(T(0)), T(0));
  TTS_EQUAL(eve::sign(T(2)), T(1));
}
