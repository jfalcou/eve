//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated_(eve::sub) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated_(eve::sub)(T(), T()), T);
}

TTS_CASE_TPL("Check eve::saturated_(eve::sub) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::saturated_(eve::sub)(T(0), T(0)), T(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(T(3), T(1)), T(2));
  TTS_EQUAL(eve::saturated_(eve::sub)(T(6), T(2)), T(4));

  TTS_EQUAL(eve::saturated_(eve::sub)(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(v_t(3), T(1)), T(2));
  TTS_EQUAL(eve::saturated_(eve::sub)(v_t(6), T(2)), T(4));

  TTS_EQUAL(eve::saturated_(eve::sub)(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::saturated_(eve::sub)(T(3), v_t(1)), T(2));
  TTS_EQUAL(eve::saturated_(eve::sub)(T(6), v_t(2)), T(4));

  if constexpr(eve::integral_value<T>)
  {
    auto vmin = eve::Valmin<T>();

    TTS_EQUAL( (eve::saturated_(eve::sub)(eve::Valmin<T>()  ,T(1)))   , vmin );
    TTS_EQUAL( (eve::saturated_(eve::sub)(eve::Valmin<v_t>(),T(1)))   , vmin );
    TTS_EQUAL( (eve::saturated_(eve::sub)(eve::Valmin<T>()  ,v_t(1))) , vmin );

    if constexpr(std::is_signed_v<v_t>)
    {
      auto vmax = eve::Valmax<T>();

      TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmax<T>()   , T(-1))) ,vmax );
      TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmax<v_t>() , T(-1))) ,vmax );
      TTS_EQUAL ( (eve::saturated_(eve::sub)(eve::Valmax<T>()   , v_t(-1))),vmax );

      TTS_EQUAL(eve::saturated_(eve::sub)(  T(-1) ,   T( 1)), T(-2));
      TTS_EQUAL(eve::saturated_(eve::sub)(  T(-2) ,   T(-6)), T( 4));
      TTS_EQUAL(eve::saturated_(eve::sub)(v_t(-1) ,   T( 1)), T(-2));
      TTS_EQUAL(eve::saturated_(eve::sub)(v_t(-2) ,   T(-6)), T( 4));
      TTS_EQUAL(eve::saturated_(eve::sub)(  T(-1) , v_t( 1)), T(-2));
      TTS_EQUAL(eve::saturated_(eve::sub)(  T(-2) , v_t(-6)), T( 4));
    }
  }
}

