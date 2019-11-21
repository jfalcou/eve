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
#include <eve/function/any.hpp>
#include <eve/function/sub.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::convert) return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int32_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int32_t;
#endif

  TTS_EXPR_IS(eve::saturated_(eve::convert)(Type(), eve::as<std::int32_t>()), target_t);
  TTS_EXPR_IS(eve::saturated_(eve::convert)(Type(), eve::int32_)     , target_t);
}

TTS_CASE("Check eve::saturated_(eve::convert) behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int32_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int32_t;
#endif

  TTS_EQUAL(eve::saturated_(eve::convert)((Type(0))          , eve::int32_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated_(eve::convert)((Type(42.69))      , eve::int32_), static_cast<target_t>(Value(42.69)) );
  if constexpr(std::is_integral_v<Value>)
  {
    // with floating value this test produces undefined behaviour
    if constexpr(sizeof(Value) >= 4)
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::int32_), eve::Valmax<target_t>());
    }
    else
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::int32_), static_cast<target_t>(eve::Valmax<Value>()));
    }
  }
  if constexpr(sizeof(Value) >= 4)
  {
    if constexpr(!std::is_signed_v<Value>)
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::int32_), target_t(0));
    }
    else
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::int32_), eve::Valmin<target_t>());
    }
  }
  else
  {
    TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::int32_), static_cast<target_t>(eve::Valmin<Value>()));
  }
}
