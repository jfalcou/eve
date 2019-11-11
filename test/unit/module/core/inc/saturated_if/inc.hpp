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
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check conditional saturated_(eve::inc) return type")
{
  using eve::saturated_;

  TTS_EXPR_IS((saturated_(eve::inc[Type()])(Type()))                , (Type));
  TTS_EXPR_IS((saturated_(eve::inc[Value()])(Type()))               , (Type));
  TTS_EXPR_IS((saturated_(eve::inc[true])(Type()))                  , (Type));
  TTS_EXPR_IS((saturated_(eve::inc[eve::logical<Type>()])(Type()))  , (Type));
  TTS_EXPR_IS((saturated_(eve::inc[eve::logical<Value>()])(Type())) , (Type));
}

TTS_CASE("Check conditional saturated_(eve::inc) behavior")
{
  using eve::saturated_;

  Type tv(2);
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  // All basic TRUE
  TTS_EQUAL(saturated_(eve::inc[ 1 ])(eve::Valmax<Type>())     , eve::Valmax<Type>());
  TTS_EQUAL(saturated_(eve::inc[ 1.0 ])(eve::Valmax<Type>())   , eve::Valmax<Type>());
  TTS_EQUAL(saturated_(eve::inc[ true ])(eve::Valmax<Type>())  , eve::Valmax<Type>());
  TTS_EQUAL(saturated_(eve::inc[ t ])(eve::Valmax<Type>())     , eve::Valmax<Type>());

  // All basic FALSE
  TTS_EQUAL(saturated_(eve::inc[ 0 ])(tv)     , tv);
  TTS_EQUAL(saturated_(eve::inc[ 0.0 ])(tv)   , tv);
  TTS_EQUAL(saturated_(eve::inc[ false ])(tv) , tv);
  TTS_EQUAL(saturated_(eve::inc[ f ])(tv)     , tv);

  // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL(saturated_(eve::inc[ m ])(tv) , eve::if_else(m,saturated_(eve::inc)(tv), tv) );
}
