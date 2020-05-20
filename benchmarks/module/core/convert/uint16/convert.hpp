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

TTS_CASE("Check eve::convert return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::uint16_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::uint16_t;
#endif

  TTS_EXPR_IS(eve::convert(EVE_TYPE(), eve::as<std::uint16_t>()), target_t);
  TTS_EXPR_IS(eve::convert(EVE_TYPE(), eve::uint16_)     , target_t);
}

TTS_CASE("Check eve::convert behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::uint16_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::uint16_t;
#endif

  TTS_EQUAL(eve::convert((EVE_TYPE(0))          , eve::uint16_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::convert((EVE_TYPE(42.69))      , eve::uint16_), static_cast<target_t>(EVE_VALUE(42.69)) );
  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::convert(eve::Valmin<EVE_TYPE>(), eve::uint16_), static_cast<target_t>(eve::Valmin<EVE_VALUE>()) );
    TTS_EQUAL(eve::convert(eve::Valmax<EVE_TYPE>(), eve::uint16_), static_cast<target_t>(eve::Valmax<EVE_VALUE>()) );
  }
}
