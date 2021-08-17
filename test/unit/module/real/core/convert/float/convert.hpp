//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/convert.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/sqr.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::convert return type", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  TTS_EXPR_IS(eve::convert(T(), eve::as<float>()), target_t);
  TTS_EXPR_IS(eve::float32(T())     , target_t);
}

TTS_CASE_TPL("Check eve::convert behavior", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::wide<float, eve::fixed<EVE_CARDINAL>>;
#else
  using target_t = float;
#endif

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::convert((T(0))          , eve::as<float>()), static_cast<target_t>(0) );
  TTS_EQUAL(eve::convert((T(42.69))      , eve::as<float>()), static_cast<target_t>(v_t(42.69)) );

  if constexpr(sizeof(v_t)<=sizeof(float))
  {
    TTS_EQUAL(eve::convert(eve::valmin(eve::as<T>()), eve::as<float>()), static_cast<target_t>(eve::valmin(eve::as<v_t>())) );
    TTS_EQUAL(eve::convert(eve::valmax(eve::as<T>()), eve::as<float>()), static_cast<target_t>(eve::valmax(eve::as<v_t>())) );
  }
}

TTS_CASE_TPL("float32", EVE_TYPE)
{
  TTS_EQUAL(eve::convert((T(0))        , eve::as<float>()), eve::float32(T(0)) );
  TTS_EQUAL(eve::convert((T(42.69))    , eve::as<float>()), eve::float32(T(42.69)));
  TTS_EQUAL(eve::convert(eve::sqr(T(2)), eve::as<float>()), eve::float32(eve::sqr)(T(2)));
}

TTS_CASE_TPL("Check eve::convert logical behavior", EVE_TYPE)
{
#if defined(EVE_SIMD_TESTS)
  using target_t = eve::logical<eve::wide<float, eve::fixed<EVE_CARDINAL>>>;
#else
  using target_t = eve::logical<float>;
#endif

  TTS_EQUAL(eve::convert(eve::logical<T>(true)  , eve::as<eve::logical<float>>()), target_t(true) );
  TTS_EQUAL(eve::convert(eve::logical<T>(false) , eve::as<eve::logical<float>>()), target_t(false) );

#if defined(EVE_SIMD_TESTS)
  eve::logical<T> mixed( [](auto i, auto) { return i%2 == 0;});
  target_t        ref( [](auto i, auto) { return i%2 == 0;});

  TTS_EQUAL(eve::convert(mixed, eve::as<eve::logical<float>>()), ref );
#endif
}
