//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::oneminus return type")
{
  TTS_EXPR_IS(eve::oneminus[ Value(0)  ](Type(0))              , (Type));
  TTS_EXPR_IS(eve::oneminus[ (Type(0)) ](Type(0))              , (Type));
  TTS_EXPR_IS(eve::oneminus[ (eve::logical<Type>(0))](Type(0)) , (Type));
  TTS_EXPR_IS(eve::oneminus[ eve::logical<Value>(0) ](Type(0)) , (Type));
  TTS_EXPR_IS(eve::oneminus[ true ](Type(0))                   , (Type));
}

TTS_CASE("Check eve::oneminus behavior")
{
  Type tv(2);
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::oneminus[ 1 ](tv)   , (Type(-1)));
  TTS_EQUAL(eve::oneminus[ 1.0 ](tv) , (Type(-1)));
  TTS_EQUAL(eve::oneminus[ true ](tv), (Type(-1)));
  TTS_EQUAL(eve::oneminus[ t ](tv)   , (Type(-1)));

  TTS_EQUAL(eve::oneminus[ 0 ](tv)     , tv);
  TTS_EQUAL(eve::oneminus[ 0.0 ](tv)   , tv);
  TTS_EQUAL(eve::oneminus[ false ](tv) , tv);
  TTS_EQUAL(eve::oneminus[ f ](tv)     , tv);

    // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_ALL_EQUAL(eve::oneminus[ m ](tv), eve::if_else(m, (Type(-1)), tv) );
}
