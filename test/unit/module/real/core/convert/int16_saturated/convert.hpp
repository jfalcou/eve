//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/convert.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated(eve::convert) return type", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int16_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::int16_t;
#endif

  TTS_EXPR_IS(eve::saturated(eve::convert)(T(), eve::as<std::int16_t>()), target_t);
}

TTS_CASE_TPL("Check eve::saturated(eve::convert) behavior", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<std::int16_t, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = std::int16_t;
#endif

  using v_t = eve::element_type_t<T>;

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::convert)((T(-42.69))    , eve::as<std::int16_t>()), static_cast<target_t>(v_t(-42.69)) );
  }

  TTS_EQUAL(eve::saturated(eve::convert)((T(0))          , eve::as<std::int16_t>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(42.69))      , eve::as<std::int16_t>()), static_cast<target_t>(v_t(42.69)) );

  if constexpr(eve::integral_value<T>)
  {
    // with floating value this test produces undefined behaviour
    if constexpr(eve::signed_value<T>)
    {
      if constexpr(sizeof(v_t) >  2)
      {
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<std::int16_t>()), (eve::valmin(eve::as<target_t>())) );
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<std::int16_t>()), (eve::valmax(eve::as<target_t>())) );
      }
      else
      {
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<std::int16_t>()), target_t(eve::valmin(eve::as<v_t>())) );
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<std::int16_t>()), target_t(eve::valmax(eve::as<v_t>())) );
      }
    }
    else //if constexpr(std::is_unsigned_v<v_t>)
    {
      if constexpr(sizeof(v_t) >=  2)
      {
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<std::int16_t>()), (target_t(0)) );
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<std::int16_t>()), (eve::valmax(eve::as<target_t>())) );
      }
      else if  constexpr(sizeof(v_t) < 2)
      {
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), eve::as<std::int16_t>()), target_t(0) );
        TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), eve::as<std::int16_t>()), target_t(eve::valmax(eve::as<v_t>())) );
      }
    }
  }
}
