//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SUB_HPP
#define SUB_HPP

#include <eve/function/sub.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE("Check sub return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::sub[ Type() ])(Type(), Type()), Type);
  TTS_EXPR_IS(eve::saturated_(eve::sub[ eve::logical<Type>() ])(Type(), Type()), Type);
  TTS_EXPR_IS(eve::saturated_(eve::sub[ true ])(Type(), Type()), Type);
}


TTS_CASE("Check saturated conditional sub behavior")
{
  Type tv{eve::Valmax<Type>()};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::saturated_(eve::sub[ 1 ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::sub[ 1.0 ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::sub[ true ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::sub[ t ])(tv, fv), eve::saturated_(eve::sub)(tv,fv));
  TTS_EQUAL(eve::saturated_(eve::sub[ 0 ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::sub[ 0.0 ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::sub[ false ])(tv, fv), tv);
  TTS_EQUAL(eve::saturated_(eve::sub[ f ])(tv, fv), tv);
}

#endif
