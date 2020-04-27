//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_not.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check logical_not return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_not(T())          ), (logical<T>));
  TTS_EXPR_IS((eve::logical_not(logical<T>()) ), (logical<T>));
}

TTS_CASE_TPL("Check eve::logical_not behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_not(T(1))             , eve::False<T>());
  TTS_EQUAL(eve::logical_not(T(0))             , eve::True<T>() );
  TTS_EQUAL(eve::logical_not(eve::Allbits<T>()), eve::False<T>());
  TTS_EQUAL(eve::logical_not(eve::True<T>())   , eve::False<T>());
  TTS_EQUAL(eve::logical_not(eve::False<T>())  , eve::True<T>() );
}

TTS_CASE_TPL("Check eve::operator! behavior", EVE_TYPE)
{
  TTS_EQUAL(!eve::True<T>()  , eve::False<T>());
  TTS_EQUAL(!eve::False<T>() , eve::True<T>());
}
