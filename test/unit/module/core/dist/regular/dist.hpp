//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dist.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::dist return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::dist(T(), T()), T);
}

TTS_CASE_TPL("Check eve::dist behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::dist(T(0), T(0)), T(0));
  TTS_EQUAL(eve::dist(T(0), T(1)), T(1));
  TTS_EQUAL(eve::dist(T(1), T(0)), T(1));
  TTS_EQUAL(eve::dist(T(1), T(1)), T(0));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::dist(T(-1), T( 1)), T(2));
    TTS_EQUAL(eve::dist(T(-2), T(-6)), T(4));
  }
}
