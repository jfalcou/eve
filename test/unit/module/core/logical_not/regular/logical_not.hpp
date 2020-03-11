//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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

TTS_CASE("Check logical_not return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_not(EVE_TYPE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_not(logical<EVE_TYPE>()) ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::logical_not behavior")
{
  TTS_EQUAL(eve::logical_not(EVE_TYPE(1))             , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_not(EVE_TYPE(0))             , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_not(eve::Allbits<EVE_TYPE>()), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_not(eve::True<EVE_TYPE>())   , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_not(eve::False<EVE_TYPE>())  , eve::True<EVE_TYPE>() );
}

TTS_CASE("Check eve::operator! behavior")
{
  TTS_EQUAL(!eve::True<EVE_TYPE>()  , eve::False<EVE_TYPE>());
  TTS_EQUAL(!eve::False<EVE_TYPE>() , eve::True<EVE_TYPE>());
}
