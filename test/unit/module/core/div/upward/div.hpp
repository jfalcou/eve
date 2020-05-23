//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE_TPL("Check div return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::upward_(eve::div)(   T() ,   T()), T);
  TTS_EXPR_IS(eve::upward_(eve::div)(   T() , v_t()), T);
  TTS_EXPR_IS(eve::upward_(eve::div)( v_t() ,   T()), T);
}

TTS_CASE_TPL("Check eve::div behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::upward_(eve::div)(   T(-1) ,   T(2)), T(0));
    TTS_EQUAL(eve::upward_(eve::div)( v_t(-1) ,   T(2)), T(0));
    TTS_EQUAL(eve::upward_(eve::div)(   T(-1) , v_t(2)), T(0));
  }

  TTS_EQUAL(eve::upward_(eve::div)(T(12), T(4)), T(3));
  TTS_EQUAL(eve::upward_(eve::div)(T(1) , T(2)), T(1));
  TTS_EQUAL(eve::upward_(eve::div)(T(4) , T(3)), T(2));

  TTS_EQUAL(eve::upward_(eve::div)(v_t(12), T(4)), T(3));
  TTS_EQUAL(eve::upward_(eve::div)(v_t(1) , T(2)), T(1));
  TTS_EQUAL(eve::upward_(eve::div)(v_t(4) , T(3)), T(2));

  TTS_EQUAL(eve::upward_(eve::div)(T(12), v_t(4)), T(3));
  TTS_EQUAL(eve::upward_(eve::div)(T(1) , v_t(2)), T(1));
  TTS_EQUAL(eve::upward_(eve::div)(T(4) , v_t(3)), T(2));
}
