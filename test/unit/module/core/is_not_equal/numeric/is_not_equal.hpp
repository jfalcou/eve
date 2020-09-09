  //==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_equal.hpp>
#include <eve/function/numeric.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::numeric_(eve::is_not_equal) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(T()            , T()           ), eve::logical<T>);
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(T()            , v_t()         ), eve::logical<T>);
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(v_t()          , T()           ), eve::logical<T>);
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(logical<T>()   , logical<T>()  ), eve::logical<T>);
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(logical<T>()   , logical<v_t>()), eve::logical<T>);
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(logical<v_t>() , logical<T>()  ), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::numeric_(eve::is_not_equal) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())), eve::False<T>());
    TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::nan(eve::as<T>()), T(4))         , eve::True<T>());
  }

  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(T(1)           , T(1) )           , eve::False<T>());
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(T(1)           , v_t(1))          , eve::False<T>());
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(T(3)           , T(1) )           , eve::True<T>() );
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(T(3)           , v_t(1))          , eve::True<T>() );
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::True<T>() , eve::True<T>())  , eve::False<T>());
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::True<T>() , eve::False<T>()) , eve::True<T>() );
}
