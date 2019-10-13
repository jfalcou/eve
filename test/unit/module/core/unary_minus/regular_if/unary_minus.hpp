//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/unary_minus.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check conditional eve::unary_minus return type")
{
  TTS_EXPR_IS(eve::unary_minus[ Value(0)  ](Type(0))              , (Type));
  TTS_EXPR_IS(eve::unary_minus[ (Type(0)) ](Type(0))              , (Type));
  TTS_EXPR_IS(eve::unary_minus[ (eve::logical<Type>(0))](Type(0)) , (Type));
  TTS_EXPR_IS(eve::unary_minus[ eve::logical<Value>(0) ](Type(0)) , (Type));
  TTS_EXPR_IS(eve::unary_minus[ true ](Type(0))                   , (Type));
}

TTS_CASE("Check conditional eve::unary_minus behavior")
{
  Type tv(2);
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::unary_minus[ 1 ](tv)   , (Type(-tv)));
  TTS_EQUAL(eve::unary_minus[ 1.0 ](tv) , (Type(-tv)));
  TTS_EQUAL(eve::unary_minus[ true ](tv), (Type(-tv)));
  TTS_EQUAL(eve::unary_minus[ t ](tv)   , (Type(-tv)));

  TTS_EQUAL(eve::unary_minus[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::unary_minus[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::unary_minus[ false ](tv) , tv);
  TTS_EQUAL(eve::unary_minus[ f ](tv)     , tv);

    // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::unary_minus[ m ](tv), eve::if_else(m,  (Type(-tv)), tv) );
}
