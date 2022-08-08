//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check eve::convert return type", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t = eve::wide<float, eve::cardinal_t<T>>;

  TTS_EXPR_IS(eve::convert(T(), eve::as<float>()), t_t);
  TTS_EXPR_IS(eve::float32(T()), t_t);
  TTS_EXPR_IS(eve::saturated(eve::convert)(T(), eve::as<float>()), t_t);
};

//==================================================================================================
// Value tests
//==================================================================================================
TTS_CASE_TPL("Check eve::convert arithmetic behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t          = eve::wide<float, eve::cardinal_t<T>>;
  using v_t          = eve::element_type_t<T>;
  constexpr auto tgt = eve::as<float>();

  TTS_EQUAL(eve::convert((T(0)), tgt), static_cast<t_t>(0));
  TTS_EQUAL(eve::convert((T(42.69)), tgt), static_cast<t_t>(v_t(42.69)));
  TTS_EQUAL(eve::convert((T(0)), tgt), eve::float32(T(0)));
  TTS_EQUAL(eve::convert((T(42.69)), tgt), eve::float32(T(42.69)));
  TTS_EQUAL(eve::convert(eve::sqr(T(2)), tgt), eve::float32(eve::sqr)(T(2)));

  if constexpr( sizeof(v_t) <= sizeof(float) )
  {
    TTS_EQUAL(eve::convert(eve::valmin(eve::as<T>()), tgt),
              static_cast<t_t>(eve::valmin(eve::as<v_t>())));
    TTS_EQUAL(eve::convert(eve::valmax(eve::as<T>()), tgt),
              static_cast<t_t>(eve::valmax(eve::as<v_t>())));
  }
};

TTS_CASE_TPL("Check saturated eve::convert arithmetic behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t          = eve::wide<float, eve::cardinal_t<T>>;
  using v_t          = eve::element_type_t<T>;
  constexpr auto tgt = eve::as<float>();

  if constexpr( std::is_same_v<v_t, double> )
  {
    TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), tgt),
              (eve::valmin(eve::as<t_t>())));
    TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), tgt),
              (eve::valmax(eve::as<t_t>())));
  }
  else
  {
    if constexpr( sizeof(v_t) <= sizeof(float) )
    {
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), tgt),
                static_cast<t_t>(eve::valmin(eve::as<v_t>())));
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), tgt),
                static_cast<t_t>(eve::valmax(eve::as<v_t>())));
    }
  }

  TTS_EQUAL(eve::saturated(eve::convert)((T(0)), tgt), static_cast<t_t>(0));
  TTS_EQUAL(eve::saturated(eve::convert)((T(42.69)), tgt), static_cast<t_t>(v_t(42.69)));
};

TTS_CASE_TPL("Check eve::convert logical behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using t_t          = eve::logical<eve::wide<float, eve::cardinal_t<T>>>;
  constexpr auto tgt = eve::as<eve::logical<float>>();

  TTS_EQUAL(eve::convert(eve::logical<T>(true), tgt), t_t(true));
  TTS_EQUAL(eve::convert(eve::logical<T>(false), tgt), t_t(false));

  eve::logical<T> mixed([](auto i, auto) { return i % 2 == 0; });
  t_t             ref([](auto i, auto) { return i % 2 == 0; });

  TTS_EQUAL(eve::convert(mixed, tgt), ref);
};
