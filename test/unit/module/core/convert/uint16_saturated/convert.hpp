//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE_TPL("Check eve::saturated_(eve::convert) return type", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::uint16_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::uint16_t;
#endif

  TTS_EXPR_IS(eve::saturated_(eve::convert)(T(), eve::as<std::uint16_t>()), target_t);
  TTS_EXPR_IS(eve::saturated_(eve::convert)(T(), eve::uint16_)     , target_t);
}

TTS_CASE_TPL("Check eve::saturated_(eve::convert) behavior", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::uint16_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::uint16_t;
#endif

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::saturated_(eve::convert)((T(0))          , eve::uint16_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated_(eve::convert)((T(42.69))      , eve::uint16_), static_cast<target_t>(v_t(42.69)) );

  if constexpr(eve::integral_value<T>)
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<T>(), eve::uint16_), (target_t(0)) );

    if constexpr(sizeof(v_t) <= 2)
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<T>(), eve::uint16_), target_t(eve::Valmax<v_t>()) );
    }
    else
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<T>(), eve::uint16_), (eve::Valmax<target_t>()) );
    }
  }
}
