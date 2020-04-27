//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/itrunc.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check itrunc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::itrunc(T()), (eve::detail::as_integer_t<T>));
}

TTS_CASE_TPL("Check eve::itrunc behavior", EVE_TYPE)
{
  using i_t = eve::detail::as_integer_t<T>;
  TTS_EQUAL(eve::itrunc(T(0)), i_t(0));
  TTS_EQUAL(eve::itrunc(T(1)), i_t(1));
  TTS_EQUAL(eve::itrunc(T(2)), i_t(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::itrunc(T(-1)), i_t(-1));
    TTS_EQUAL(eve::itrunc(T(-2)), i_t(-2));
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::itrunc(T(-1.3)), i_t(-1));
   TTS_EQUAL(eve::itrunc(T(-1.5)), i_t(-1));
   TTS_EQUAL(eve::itrunc(T(-1.6)), i_t(-1));
   TTS_EQUAL(eve::itrunc(T(1.3)) , i_t(1));
   TTS_EQUAL(eve::itrunc(T(1.5)) , i_t(1));
   TTS_EQUAL(eve::itrunc(T(1.6)) , i_t(1));
  }
}
