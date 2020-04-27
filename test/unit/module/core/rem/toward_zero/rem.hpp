//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE_TPL("Check rem return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::rem(T(), T() , eve::toward_zero_), T);
  TTS_EXPR_IS(eve::rem(T(), v_t() , eve::toward_zero_), T);
  TTS_EXPR_IS(eve::rem(v_t(), T() , eve::toward_zero_), T);
}

TTS_CASE_TPL("Check eve::rem behavior", EVE_TYPE)
{
  if constexpr(eve::integral_value<T> && eve::signed_value<T>)
  {
    TTS_EQUAL(eve::rem(eve::Mone<T>()  , T{2} , eve::toward_zero_), T(-1));
    TTS_EQUAL(eve::rem(eve::Mone<v_t>() , T{2} , eve::toward_zero_), T(-1));
    TTS_EQUAL(eve::rem(eve::Mone<T>()  , v_t{2}, eve::toward_zero_), T(-1));
    TTS_EQUAL(eve::rem(T(-4)  , T{3} , eve::toward_zero_), T(-1));
    TTS_EQUAL(eve::rem(v_t(-4) , T{3} , eve::toward_zero_), T(-1));
    TTS_EQUAL(eve::rem(T(-4)  , v_t{3}, eve::toward_zero_), T(-1));
  }
  TTS_EQUAL(eve::rem(T{12}, T{4}, eve::toward_zero_), T{0});
  TTS_EQUAL(eve::rem(T{1} , T{2}, eve::toward_zero_), T(1));
  TTS_EQUAL(eve::rem(T{4} , T{3}, eve::toward_zero_), T(1));

  TTS_EQUAL(eve::rem(v_t{12}, T{4}, eve::toward_zero_), T{0});
  TTS_EQUAL(eve::rem(v_t{1} , T{2}, eve::toward_zero_), T(1));
  TTS_EQUAL(eve::rem(v_t{4} , T{3}, eve::toward_zero_), T(1));

  TTS_EQUAL(eve::rem(T{12}, v_t{4}, eve::toward_zero_), T{0});
  TTS_EQUAL(eve::rem(T{1} , v_t{2}, eve::toward_zero_), T(1));
  TTS_EQUAL(eve::rem(T{4} , v_t{3}, eve::toward_zero_), T(1));
}
