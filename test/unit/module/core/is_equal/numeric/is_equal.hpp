//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_equal.hpp>
#include <eve/function/numeric.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::numeric_(eve::is_equal) return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS( eve::numeric_(eve::is_equal)(T()          , T()          ), (logical<T>));
  TTS_EXPR_IS( eve::numeric_(eve::is_equal)(T()          , v_t()         ), (logical<T>));
  TTS_EXPR_IS( eve::numeric_(eve::is_equal)(v_t()         , T()          ), (logical<T>));
  TTS_EXPR_IS( eve::numeric_(eve::is_equal)(logical<T>() , logical<T>() ), (logical<T>));
  TTS_EXPR_IS( eve::numeric_(eve::is_equal)(logical<T>() , logical<v_t>()), (logical<T>));
  TTS_EXPR_IS( eve::numeric_(eve::is_equal)(logical<v_t>(), logical<T>() ), (logical<T>));
}

TTS_CASE_TPL("Check eve::numeric_(eve::is_equal) behavior", EVE_TYPE)
{
  using eve::logical;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::numeric_(eve::is_equal)(eve::Nan<T>(), eve::Nan<T>())   , eve::True<T>());
    TTS_EQUAL(eve::numeric_(eve::is_equal)(eve::Nan<T>(), T(4))            , eve::False<T>());
  }

  TTS_EQUAL(eve::numeric_(eve::is_equal)(T(1)           , T(1) )           , eve::True<T>() );
  TTS_EQUAL(eve::numeric_(eve::is_equal)(T(1)           , v_t(1))           , eve::True<T>() );
  TTS_EQUAL(eve::numeric_(eve::is_equal)(T(3)           , T(1) )           , eve::False<T>());
  TTS_EQUAL(eve::numeric_(eve::is_equal)(T(3)           , v_t(1))           , eve::False<T>());
  TTS_EQUAL(eve::numeric_(eve::is_equal)(eve::True<T>() , eve::True<T>())  , eve::True<T>() );
  TTS_EQUAL(eve::numeric_(eve::is_equal)(eve::True<T>() , eve::False<T>()) , eve::False<T>());
}
