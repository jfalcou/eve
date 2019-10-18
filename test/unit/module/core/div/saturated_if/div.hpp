//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>


TTS_CASE("Check conditional saturated(eve::div) return type")
{
  TTS_EXPR_IS( (eve::saturated_(eve::div[ Type()              ])(Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::saturated_(eve::div[ eve::logical<Type>()])(Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::saturated_(eve::div[ true                ])(Type(), Type())), (Type));
}

TTS_CASE("Check conditional saturated(eve::div) behavior")
{
  Type tv{eve::Valmax<Type>()};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::saturated_(eve::div[ 1 ])(tv, fv)    , eve::saturated_(eve::div)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::div[ 1.0 ])(tv, fv)  , eve::saturated_(eve::div)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::div[ true ])(tv, fv) , eve::saturated_(eve::div)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::div[ t ])(tv, fv)    , eve::saturated_(eve::div)(tv,fv));

  TTS_EQUAL(eve::saturated_(eve::div[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::saturated_(eve::div[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::saturated_(eve::div[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::div[ f ])(tv, fv)    , tv);

  // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL ( eve::saturated_(eve::div[ m ])(tv, fv),
                  eve::if_else(m, eve::saturated_(eve::div)(tv,fv), tv)
                );

}
