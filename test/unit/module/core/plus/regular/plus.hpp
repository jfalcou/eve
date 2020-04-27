//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/plus.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::plus return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::plus(T()), T);
}

TTS_CASE_TPL("Check eve::plus behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::plus(T(1)), (T(1)));
}

TTS_CASE_TPL("Check eve::plus with 2 parameters behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::plus(T(1), T(1)), (T(2)));
}

TTS_CASE_TPL("Check eve::plus with 3 parameter sbehavior", EVE_TYPE)
{
  TTS_EQUAL(eve::plus(T(1) > T(2), T(1), T(1)), (T(1)));
  TTS_EQUAL(eve::plus(T(1) < T(2), T(1), T(1)), (T(2)));
}
