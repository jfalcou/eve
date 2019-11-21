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
  using target_t = eve::wide<std::uint8_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::uint8_t;
#endif

  TTS_EXPR_IS(eve::saturated_(eve::convert)(Type(), eve::as<std::uint8_t>()), target_t);
  TTS_EXPR_IS(eve::saturated_(eve::convert)(Type(), eve::uint8_)     , target_t);
}

TTS_CASE("Check eve::saturated_(eve::convert) behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::uint8_t, eve::fixed<Cardinal>>;
#else
  using target_t = std::uint8_t;
#endif

  TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<Type>(), eve::uint8_), static_cast<target_t>(0) ); 
  TTS_EQUAL(eve::saturated_(eve::convert)((Type(0))          , eve::uint8_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated_(eve::convert)((Type(42.69))      , eve::uint8_), static_cast<target_t>(Value(42.69)) );
   if constexpr(std::is_integral_v<Value>)
  {
    // with floating value this test produces undefined behaviour
    if constexpr(std::is_same_v<Value, std::int8_t>)
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::uint8_), target_t(127) );
    }
    else
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<Type>(), eve::uint8_), target_t(255) );
    }
  }
}
