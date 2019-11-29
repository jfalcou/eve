//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lookup.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::lookup return type")
{
  TTS_EXPR_IS((eve::lookup(Type() , eve::detail::as_integer_t<Type >())), (Type) );
  TTS_EXPR_IS((eve::lookup(Value(), eve::detail::as_integer_t<Value>())), (Value));
}

TTS_CASE("Check eve::lookup behavior")
{
  using index_t = eve::detail::as_integer_t<Type>;

  TTS_EQUAL(eve::lookup((Type(42)), index_t( 0) ), (Type(42)) );
  TTS_EQUAL(eve::lookup((Type(42)), index_t(-1) ), (Type(0))  );

  #if defined(EVE_SIMD_TESTS)

  Type    value{[](auto i, auto)       { return static_cast<Value>(1+i); } };
  Type    reference{[](auto i, auto c) { return static_cast<Value>(c-i); } };
  index_t indexes{[](auto i, auto c) { return c-i-1; } };

  TTS_EQUAL(eve::lookup(value, indexes) , reference );
  TTS_EQUAL(value[indexes]              , reference );

  #endif
}

