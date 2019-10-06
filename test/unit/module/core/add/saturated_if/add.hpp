//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/add.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check add return type")
{
  TTS_EXPR_IS( (eve::saturated_(eve::add[ Type()              ])(Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::saturated_(eve::add[ eve::logical<Type>()])(Type(), Type())), (Type));
  TTS_EXPR_IS( (eve::saturated_(eve::add[ true                ])(Type(), Type())), (Type));
}

TTS_CASE("Check saturated conditional add behavior")
{
  Type tv{eve::Valmax<Type>()};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_ALL_EQUAL(eve::saturated_(eve::add[ 1 ])(tv, fv)    , eve::saturated_(eve::add)(tv,fv));
  TTS_ALL_EQUAL(eve::saturated_(eve::add[ 1.0 ])(tv, fv)  , eve::saturated_(eve::add)(tv,fv));
  TTS_ALL_EQUAL(eve::saturated_(eve::add[ true ])(tv, fv) , eve::saturated_(eve::add)(tv,fv));
  TTS_ALL_EQUAL(eve::saturated_(eve::add[ t ])(tv, fv)    , eve::saturated_(eve::add)(tv,fv));

  TTS_ALL_EQUAL(eve::saturated_(eve::add[ 0 ])(tv, fv)    , tv);
  TTS_ALL_EQUAL(eve::saturated_(eve::add[ 0.0 ])(tv, fv)  , tv);
  TTS_ALL_EQUAL(eve::saturated_(eve::add[ false ])(tv, fv), tv);
  TTS_ALL_EQUAL(eve::saturated_(eve::add[ f ])(tv, fv)    , tv);

  // Mixed case
  eve::as_logical_t<Type> m;
  std::for_each ( tts::detail::begin(m), tts::detail::end(m)
                , [k = true](auto& e) mutable { e = k; k = !k; }
                );

  TTS_ALL_EQUAL ( eve::saturated_(eve::add[ m ])(tv, fv),
                  eve::if_else(m, eve::saturated_(eve::add)(tv,fv), tv)
                );

}
