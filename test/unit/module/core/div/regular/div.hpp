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
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::div return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::div(T(), T()), T);
}

TTS_CASE_TPL("Check eve::div behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::div(T( 0), T(1)), (T(0  )));
  TTS_EQUAL(eve::div(T( 1), T(1)), (T(1  )));
  TTS_EQUAL(eve::div(T(12), T(4)), (T(3  )));
  TTS_EQUAL(eve::div(T( 1), T(2)), (T(0.5)));

  TTS_EQUAL(eve::div(v_t( 0), T(1)), (T(0  )));
  TTS_EQUAL(eve::div(v_t( 1), T(1)), (T(1  )));
  TTS_EQUAL(eve::div(v_t(12), T(4)), (T(3  )));
  TTS_EQUAL(eve::div(v_t( 1), T(2)), (T(0.5)));

  TTS_EQUAL(eve::div(T( 0), v_t(1)), (T(0  )));
  TTS_EQUAL(eve::div(T( 1), v_t(1)), (T(1  )));
  TTS_EQUAL(eve::div(T(12), v_t(4)), (T(3  )));
  TTS_EQUAL(eve::div(T( 1), v_t(2)), (T(0.5)));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::div(eve::Valmax<T>(), T(2)),  T(eve::Valmax<v_t>()/2));
    TTS_EQUAL(eve::div(eve::Valmax<v_t>(), T(2)), T(eve::Valmax<v_t>()/2));
    TTS_EQUAL(eve::div(eve::Valmax<T>(), v_t(2)), T(eve::Valmax<v_t>()/2));

    TTS_EQUAL(eve::div(eve::Valmax<T>(), T(1)),  (eve::Valmax<T>()));
    TTS_EQUAL(eve::div(eve::Valmax<v_t>(), T(1)), (eve::Valmax<T>()));
    TTS_EQUAL(eve::div(eve::Valmax<T>(), v_t(1)), (eve::Valmax<T>()));
  }

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::div(T(-1), T(1)) , (T(-1)));
    TTS_EQUAL(eve::div(T(-6), T(-2)), (T( 3)));

    TTS_EQUAL(eve::div(v_t(-1), T(1)) , (T(-1)));
    TTS_EQUAL(eve::div(v_t(-6), T(-2)), (T( 3)));

    TTS_EQUAL(eve::div(T(-1), v_t(1)) , (T(-1)));
    TTS_EQUAL(eve::div(T(-6), v_t(-2)), (T( 3)));
  }
}
