//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/convert.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::convert return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<Cardinal>>;
#else
  using target_t = float;
#endif

  TTS_EXPR_IS(eve::convert(Type(), eve::as<float>()), target_t);
  TTS_EXPR_IS(eve::convert(Type(), eve::single_)     , target_t);
}

TTS_CASE("Check eve::convert behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<Cardinal>>;
#else
  using target_t = float;
#endif

  TTS_EQUAL(eve::convert(eve::Valmin<Type>(), eve::single_), static_cast<target_t>(eve::Valmin<Value>()) );
  TTS_EQUAL(eve::convert((Type(0))          , eve::single_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::convert((Type(42.69))      , eve::single_), static_cast<target_t>(Value(42.69)) );
  TTS_EQUAL(eve::convert(eve::Valmax<Type>(), eve::single_), static_cast<target_t>(eve::Valmax<Value>()) );
}
