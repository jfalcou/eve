//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mul.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>


TTS_CASE("Check conditional saturated(eve::mul) return type")
{
  TTS_EXPR_IS( (eve::saturated_(eve::mul[ Type()              ])(Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::saturated_(eve::mul[ eve::logical<Type>()])(Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::saturated_(eve::mul[ true                ])(Type(), Type())), (Type));
}

TTS_CASE("Check conditional saturated(eve::mul) behavior")
{
  Type fv{eve::Valmax<Type>()};
  Type tv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::saturated_(eve::mul[ 1 ])(tv, fv)    , eve::saturated_(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::mul[ 1.0 ])(tv, fv)  , eve::saturated_(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::mul[ true ])(tv, fv) , eve::saturated_(eve::mul)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::mul[ t ])(tv, fv)    , eve::saturated_(eve::mul)(tv,fv));

  TTS_EQUAL(eve::saturated_(eve::mul[ 0 ])(tv, fv)    , tv);
  TTS_EQUAL(eve::saturated_(eve::mul[ 0.0 ])(tv, fv)  , tv);
  TTS_EQUAL(eve::saturated_(eve::mul[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::mul[ f ])(tv, fv)    , tv);

  // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_EQUAL ( eve::saturated_(eve::mul[ m ])(tv, fv),
                  eve::if_else(m, eve::saturated_(eve::mul)(tv,fv), tv)
                );

}
