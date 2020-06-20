//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/floor.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check ifloor return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::toint_<T>(eve::floor)(T())), (eve::detail::as_integer_t<T>));
}

TTS_CASE_TPL("Check eve::toint_<EVE_TYPE>(eve::floor) behavior", EVE_TYPE)
{
  using i_t = eve::detail::as_integer_t<T>;

  TTS_EQUAL(eve::toint_<T>(eve::floor)(T(0)), i_t(0));
  TTS_EQUAL(eve::toint_<T>(eve::floor)(T(1)), i_t(1));
  TTS_EQUAL(eve::toint_<T>(eve::floor)(T(2)), i_t(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::toint_<T>(eve::floor)(T(-1)), i_t(-1));
    TTS_EQUAL(eve::toint_<T>(eve::floor)(T(-2)), i_t(-2));
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::toint_<T>(eve::floor)(T(-1.3)), i_t(-2));
   TTS_EQUAL(eve::toint_<T>(eve::floor)(T(-1.5)), i_t(-2));
   TTS_EQUAL(eve::toint_<T>(eve::floor)(T(-1.6)), i_t(-2));
   TTS_EQUAL(eve::toint_<T>(eve::floor)(T( 1.3)), i_t( 1));
   TTS_EQUAL(eve::toint_<T>(eve::floor)(T( 1.5)), i_t( 1));
   TTS_EQUAL(eve::toint_<T>(eve::floor)(T( 1.6)), i_t( 1));
  }
}
