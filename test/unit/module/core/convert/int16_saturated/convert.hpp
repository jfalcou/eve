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

TTS_CASE("Check eve::saturated_(eve::convert) return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int16_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int16_t;
#endif

  TTS_EXPR_IS(eve::saturated_(eve::convert)(Type(), eve::as<std::int16_t>()), target_t);
  TTS_EXPR_IS(eve::saturated_(eve::convert)(Type(), eve::int16_)     , target_t);
}

TTS_CASE("Check eve::saturated_(eve::convert) behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int16_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::int16_t;
#endif
  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::convert)((Type(-42.69))    , eve::int16_), static_cast<target_t>(Value(-42.69)) );
  }
  
  TTS_EQUAL(eve::saturated_(eve::convert)((Type(0))          , eve::int16_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated_(eve::convert)((Type(42.69))      , eve::int16_), static_cast<target_t>(Value(42.69)) );
  if constexpr(std::is_integral_v<Value>)
  {
    // with floating value this test produces undefined behaviour
    if constexpr(std::is_signed_v<Value>)
    {
      if constexpr(sizeof(Value) >  2)
      {
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::int16_), (eve::Valmin<target_t>()) );
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::int16_), (eve::Valmax<target_t>()) );
      }
      else
      {
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::int16_), target_t(eve::Valmin<Value>()) );
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::int16_), target_t(eve::Valmax<Value>()) );       
      }
    }
    else //if constexpr(std::is_unsigned_v<Value>)
    {
      if constexpr(sizeof(Value) >=  2)
      {
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::int16_), (target_t(0)) );
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::int16_), (eve::Valmax<target_t>()) );
      }
      else if  constexpr(sizeof(Value) < 2)
      {
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::int16_), target_t(0) );
        TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::int16_), target_t(eve::Valmax<Value>()) );       
      }
    }
  }
}
