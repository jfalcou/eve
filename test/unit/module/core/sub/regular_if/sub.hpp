//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <algorithm>

TTS_CASE("Check eve::sub[condition] return type")
{
  TTS_EXPR_IS( (eve::sub[ Type() ](Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::sub[ eve::logical<Type>() ](Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::sub[ true ](Type(), Type())), (Type));
}

TTS_CASE("Check eve::sub[condition] behavior")
{
  Type tv{5};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  // All basic TRUE
  TTS_EQUAL(eve::sub[ 1 ](tv, fv)     , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ 1.0 ](tv, fv)   , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ true ](tv, fv)  , eve::sub(tv,fv));
  TTS_EQUAL(eve::sub[ t ](tv, fv)     , eve::sub(tv,fv));

  // All basic FALSE
  TTS_EQUAL(eve::sub[ 0 ](tv, fv)     , tv);
  TTS_EQUAL(eve::sub[ 0.0 ](tv, fv)   , tv);
  TTS_EQUAL(eve::sub[ false ](tv, fv) , tv);
  TTS_EQUAL(eve::sub[ f ](tv, fv)     , tv);

  // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(eve::sub[ m ](tv, fv) , eve::if_else(m,eve::sub(tv,fv), tv) );
}
