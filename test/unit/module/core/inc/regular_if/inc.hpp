//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check conditional eve::inc return type")
{
  TTS_EXPR_IS((eve::inc[Type()](Type()))                , (Type));
  TTS_EXPR_IS((eve::inc[Value()](Type()))               , (Type));
  TTS_EXPR_IS((eve::inc[true](Type()))                  , (Type));
  TTS_EXPR_IS((eve::inc[eve::logical<Type>()](Type()))  , (Type));
  TTS_EXPR_IS((eve::inc[eve::logical<Value>()](Type())) , (Type));
}

TTS_CASE("Check conditional eve::inc behavior")
{
  Type tv(2);
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  // All basic TRUE
  TTS_EQUAL(eve::inc[ 1 ](tv)     , eve::inc(tv));
  TTS_EQUAL(eve::inc[ 1.0 ](tv)   , eve::inc(tv));
  TTS_EQUAL(eve::inc[ true ](tv)  , eve::inc(tv));
  TTS_EQUAL(eve::inc[ t ](tv)     , eve::inc(tv));

  // All basic FALSE
  TTS_EQUAL(eve::inc[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::inc[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::inc[ false ](tv) , tv);
  TTS_EQUAL(eve::inc[ f ](tv)     , tv);

  // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::inc[ m ](tv) , eve::if_else(m,eve::inc(tv), tv) );
}
