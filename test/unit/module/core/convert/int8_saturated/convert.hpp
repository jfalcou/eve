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

TTS_CASE("Check eve::saturated(eve::convert) return type")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int8_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::int8_t;
#endif

  TTS_EXPR_IS(eve::saturated(eve::convert)(EVE_TYPE(), eve::as<std::int8_t>()), target_t);
}

TTS_CASE("Check eve::saturated(eve::convert) behavior")
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int8_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::int8_t;
#endif


  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::saturated(eve::convert)((EVE_TYPE(-42.69))    , eve::as<std::int8_t>()), static_cast<target_t>(EVE_VALUE(-42.69)) );
  }

  TTS_EQUAL(eve::saturated(eve::convert)((EVE_TYPE(0))          , eve::as<std::int8_t>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((EVE_TYPE(42.69))      , eve::as<std::int8_t>()), static_cast<target_t>(EVE_VALUE(42.69)) );

  if constexpr(eve::integral_value<EVE_TYPE>)
  {
    // with floating value this test produces undefined behaviour
    if constexpr(sizeof(EVE_VALUE) >= 2)
    {
      if constexpr(eve::signed_value<EVE_TYPE>)
      {
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<EVE_TYPE>()), eve::as<std::int8_t>()), eve::valmin(eve::as<target_t>()));
      }
      else
      {
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<EVE_TYPE>()), eve::as<std::int8_t>()), target_t(0));
      }
    }
    else
    {
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<EVE_TYPE>()), eve::as<std::int8_t>()), (eve::valmax(eve::as<target_t>())) );
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<EVE_TYPE>()), eve::as<std::int8_t>()), static_cast<target_t>(eve::valmin(eve::as<EVE_VALUE>())) );
    }
  }
}
