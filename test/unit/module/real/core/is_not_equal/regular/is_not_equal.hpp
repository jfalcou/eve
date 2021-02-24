//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_equal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::is_not_equal return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  TTS_EXPR_IS(eve::is_not_equal(T()            , T()           ), eve::logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(T()            , v_t()         ), eve::logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(v_t()          , T()           ), eve::logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(logical<T>()   , logical<T>()  ), eve::logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(logical<T>()   , logical<v_t>()), eve::logical<T>);
  TTS_EXPR_IS(eve::is_not_equal(logical<v_t>() , logical<T>()  ), eve::logical<T>);

}

TTS_CASE_TPL("Check eve::is_not_equal behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_not_equal(eve::nan(eve::as<T>()), eve::nan(eve::as<T>()))   , eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_not_equal(eve::nan(eve::as<T>()), T(4))            , eve::true_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_not_equal(T(1)           , T(1) )           , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_not_equal(T(1)           , v_t(1))           , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_not_equal(T(3)           , T(1) )           , eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_not_equal(T(3)           , v_t(1))           , eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_not_equal(eve::true_(eve::as<T>()) , eve::true_(eve::as<T>()))  , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_not_equal(eve::true_(eve::as<T>()) , eve::false_(eve::as<T>())) , eve::true_(eve::as<T>()));

  #if defined(EVE_SIMD_TESTS)
  eve::logical<T> mixed1([](auto i, auto) { return i%3 == 0; });
  eve::logical<T> mixed2([](auto i, auto) { return i%2 == 0; });
  eve::logical<T> ref([mixed1,mixed2](auto i, auto) { return mixed1.get(i) != mixed2.get(i); });

  TTS_EQUAL( eve::is_not_equal(mixed1,mixed2), ref);
  #endif
}
