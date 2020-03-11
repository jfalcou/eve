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
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::convert) return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  TTS_EXPR_IS(eve::saturated_(eve::convert)(EVE_TYPE(), eve::as<float>()), target_t);
  TTS_EXPR_IS(eve::saturated_(eve::convert)(EVE_TYPE(), eve::single_)     , target_t);
}

TTS_CASE("Check eve::saturated_(eve::convert) behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  if constexpr(std::is_same_v<EVE_VALUE, double>)
  {
    TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<EVE_TYPE>(), eve::single_), (eve::Valmin<target_t>()) );
    TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<EVE_TYPE>(), eve::single_), (eve::Valmax<target_t>()) );
  }
  else
  {
    if constexpr(sizeof(EVE_VALUE)<=sizeof(float))
    {
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmin<EVE_TYPE>(), eve::single_), static_cast<target_t>(eve::Valmin<EVE_VALUE>()) );
      TTS_EQUAL(eve::saturated_(eve::convert)(eve::Valmax<EVE_TYPE>(), eve::single_), static_cast<target_t>(eve::Valmax<EVE_VALUE>()) );
    }
  }

  TTS_EQUAL(eve::saturated_(eve::convert)((EVE_TYPE(0))          , eve::single_), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated_(eve::convert)((EVE_TYPE(42.69))      , eve::single_), static_cast<target_t>(EVE_VALUE(42.69)) );
}
