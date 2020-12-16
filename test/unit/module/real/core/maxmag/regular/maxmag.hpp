//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/maxmag.hpp>

TTS_CASE_TPL("Check eve::maxmag return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::maxmag(T(0)  , T(0) ) , T);
  TTS_EXPR_IS(eve::maxmag(v_t(0) , T(0) ) , T);
  TTS_EXPR_IS(eve::maxmag(T(0)  , v_t(0)) , T);
}

TTS_CASE_TPL("Check eve::maxmag behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::maxmag(T(0), T(0)), T(0));
  TTS_EQUAL(eve::maxmag(T(0), T(1)), T(1));
  TTS_EQUAL(eve::maxmag(T(1), T(0)), T(1));
  TTS_EQUAL(eve::maxmag(T(1), T(1)), T(1));

  TTS_EQUAL(eve::maxmag(v_t(0), T(0)), T(0));
  TTS_EQUAL(eve::maxmag(v_t(0), T(1)), T(1));
  TTS_EQUAL(eve::maxmag(v_t(1), T(0)), T(1));
  TTS_EQUAL(eve::maxmag(v_t(1), T(1)), T(1));

  TTS_EQUAL(eve::maxmag(T(0), v_t(0)), T(0));
  TTS_EQUAL(eve::maxmag(T(0), v_t(1)), T(1));
  TTS_EQUAL(eve::maxmag(T(1), v_t(0)), T(1));
  TTS_EQUAL(eve::maxmag(T(1), v_t(1)), T(1));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::maxmag(static_cast<T>(-1), T(2)), T(2));
    TTS_EQUAL(eve::maxmag(static_cast<T>(-2), T(1)), static_cast<T>(-2));
    TTS_EQUAL(eve::maxmag(static_cast<T>(-2), T(2)), T(2));

    TTS_EQUAL(eve::maxmag(static_cast<T>(-1), v_t(2)), T(2));
    TTS_EQUAL(eve::maxmag(static_cast<T>(-2), v_t(1)), static_cast<T>(-2));
    TTS_EQUAL(eve::maxmag(static_cast<T>(-2), v_t(2)), T(2));

    TTS_EQUAL(eve::maxmag(static_cast<v_t>(-1), T(2)), T(2));
    TTS_EQUAL(eve::maxmag(static_cast<v_t>(-2), T(1)), static_cast<T>(-2));
    TTS_EQUAL(eve::maxmag(static_cast<v_t>(-2), T(2)), T(2));
  }
}
