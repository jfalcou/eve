//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check eve::convert return type", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using t_t = eve::wide<std::uint8_t, eve::cardinal_t<T>>;

  TTS_EXPR_IS(eve::convert(T()  , eve::as<std::uint8_t>())              , t_t);
  TTS_EXPR_IS(eve::uint8(T())                                           , t_t);
  TTS_EXPR_IS(eve::saturated(eve::convert)(T(), eve::as<std::uint8_t>()), t_t);
};

//==================================================================================================
// Value tests
//==================================================================================================
EVE_TEST_TYPES( "Check eve::convert arithmetic behavior", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using t_t = eve::wide<std::uint8_t, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  constexpr auto tgt = eve::as<std::uint8_t>();

  TTS_EQUAL(eve::convert((T(0))     , tgt), static_cast<t_t>(0) );
  TTS_EQUAL(eve::convert((T(42.69)) , tgt), static_cast<t_t>(v_t(42.69)) );

   if constexpr(eve::integral_value<T>)
  {
    // with floating value this test produces undefined behaviour
    TTS_EQUAL(eve::convert(eve::valmax(eve::as<T>()), tgt), static_cast<t_t>(eve::valmax(eve::as<v_t>())) );
    TTS_EQUAL(eve::convert(eve::valmin(eve::as<T>()), tgt), static_cast<t_t>(eve::valmin(eve::as<v_t>())) );
  }
};

EVE_TEST_TYPES( "Check saturated eve::convert arithmetic behavior", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using t_t = eve::wide<std::uint8_t, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  constexpr auto tgt = eve::as<std::uint8_t>();

  TTS_EQUAL(eve::saturated(eve::convert)(eve::valmin(eve::as<T>()), tgt), static_cast<t_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(0))          , tgt), static_cast<t_t>(0) );
  TTS_EQUAL(eve::saturated(eve::convert)((T(42.69))      , tgt), static_cast<t_t>(v_t(42.69)) );

  if constexpr(eve::integral_value<T>)
  {
    // with floating value this test produces undefined behaviour
    if constexpr(std::is_same_v<v_t, std::int8_t>)
    {
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), tgt), t_t(127) );
    }
    else
    {
      TTS_EQUAL(eve::saturated(eve::convert)(eve::valmax(eve::as<T>()), tgt), t_t(255) );
    }
  }
};

EVE_TEST_TYPES( "Check eve::convert logical behavior", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using t_t  = eve::logical<eve::wide<std::uint8_t, eve::cardinal_t<T>>>;
  constexpr auto tgt = eve::as<eve::logical<std::uint8_t>>();

  TTS_EQUAL(eve::convert(eve::logical<T>(true)  , tgt), t_t(true) );
  TTS_EQUAL(eve::convert(eve::logical<T>(false) , tgt), t_t(false) );

  eve::logical<T> mixed( [](auto i, auto) { return i%2 == 0;});
  t_t             ref( [](auto i, auto) { return i%2 == 0;});

  TTS_EQUAL(eve::convert(mixed, tgt), ref );
};
