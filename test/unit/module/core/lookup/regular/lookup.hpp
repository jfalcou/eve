//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lookup.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::lookup return type")
{
  TTS_EXPR_IS((eve::lookup(EVE_TYPE() , eve::detail::as_integer_t<EVE_TYPE >())), (EVE_TYPE) );
  TTS_EXPR_IS((eve::lookup(EVE_VALUE(), eve::detail::as_integer_t<EVE_VALUE>())), (EVE_VALUE));
}

TTS_CASE("Check eve::lookup behavior")
{
  using index_t = eve::detail::as_integer_t<EVE_TYPE>;

  TTS_EQUAL(eve::lookup((EVE_TYPE(42)), index_t( 0) ), (EVE_TYPE(42)) );
  TTS_EQUAL(eve::lookup((EVE_TYPE(42)), index_t(-1) ), (EVE_TYPE(0))  );

  #if defined(EVE_SIMD_TESTS)

  EVE_TYPE    value{[](auto i, auto)       { return static_cast<EVE_VALUE>(1+i); } };
  EVE_TYPE    reference{[](auto i, auto c) { return static_cast<EVE_VALUE>(c-i); } };
  index_t indexes{[](auto i, auto c) { return c-i-1; } };

  TTS_EQUAL(eve::lookup(value, indexes) , reference );
  TTS_EQUAL(value[indexes]              , reference );

  #endif
}

