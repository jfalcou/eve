//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/sub.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated(eve::sub) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated(eve::sub)(T(), T()), T);
}

TTS_CASE_TPL("Check eve::saturated(eve::sub) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::saturated(eve::sub)(T(0), T(0)), T(0));
  TTS_EQUAL(eve::saturated(eve::sub)(T(3), T(1)), T(2));
  TTS_EQUAL(eve::saturated(eve::sub)(T(6), T(2)), T(4));

  TTS_EQUAL(eve::saturated(eve::sub)(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::saturated(eve::sub)(v_t(3), T(1)), T(2));
  TTS_EQUAL(eve::saturated(eve::sub)(v_t(6), T(2)), T(4));

  TTS_EQUAL(eve::saturated(eve::sub)(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::saturated(eve::sub)(T(3), v_t(1)), T(2));
  TTS_EQUAL(eve::saturated(eve::sub)(T(6), v_t(2)), T(4));

  if constexpr(eve::integral_value<T>)
  {
    auto vmin = eve::valmin(eve::as<T>());

    TTS_EQUAL( (eve::saturated(eve::sub)(eve::valmin(eve::as<T>())  ,T(1)))   , vmin );
    TTS_EQUAL( (eve::saturated(eve::sub)(eve::valmin(eve::as<v_t>()),T(1)))   , vmin );
    TTS_EQUAL( (eve::saturated(eve::sub)(eve::valmin(eve::as<T>())  ,v_t(1))) , vmin );

    if constexpr(std::is_signed_v<v_t>)
    {
      auto vmax = eve::valmax(eve::as<T>());

      TTS_EQUAL ( (eve::saturated(eve::sub)(eve::valmax(eve::as<T>())   , T(-1))) ,vmax );
      TTS_EQUAL ( (eve::saturated(eve::sub)(eve::valmax(eve::as<v_t>()) , T(-1))) ,vmax );
      TTS_EQUAL ( (eve::saturated(eve::sub)(eve::valmax(eve::as<T>())   , v_t(-1))),vmax );

      TTS_EQUAL(eve::saturated(eve::sub)(  T(-1) ,   T( 1)), T(-2));
      TTS_EQUAL(eve::saturated(eve::sub)(  T(-2) ,   T(-6)), T( 4));
      TTS_EQUAL(eve::saturated(eve::sub)(v_t(-1) ,   T( 1)), T(-2));
      TTS_EQUAL(eve::saturated(eve::sub)(v_t(-2) ,   T(-6)), T( 4));
      TTS_EQUAL(eve::saturated(eve::sub)(  T(-1) , v_t( 1)), T(-2));
      TTS_EQUAL(eve::saturated(eve::sub)(  T(-2) , v_t(-6)), T( 4));
    }
  }
}

