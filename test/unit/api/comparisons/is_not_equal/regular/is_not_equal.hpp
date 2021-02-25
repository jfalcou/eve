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

TTS_CASE_TPL("Check eve::operator!= return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  TTS_EXPR_IS(T()   != T()  , eve::logical<T>);
  TTS_EXPR_IS(T()   != v_t(), eve::logical<T>);
  TTS_EXPR_IS(v_t() != T()  , eve::logical<T>);

  TTS_EXPR_IS(eve::logical<T>()   != eve::logical<T>()  , eve::logical<T>);
  TTS_EXPR_IS(eve::logical<T>()   != eve::logical<v_t>(), eve::logical<T>);
  TTS_EXPR_IS(eve::logical<v_t>() != eve::logical<T>()  , eve::logical<T>);
}

TTS_CASE_TPL("Check eve::operator!= behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL((eve::nan(eve::as<T>()) != eve::nan(eve::as<T>()))   , eve::true_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) != T(4))            , eve::true_(eve::as<T>()));
  }

  TTS_EQUAL( (T(1)           != T(1) )                              , eve::false_(eve::as<T>()));
  TTS_EQUAL( (T(1)           != v_t(1))                             , eve::false_(eve::as<T>()));
  TTS_EQUAL( (T(3)           != T(1) )                              , eve::true_(eve::as<T>()) );
  TTS_EQUAL( (T(3)           != v_t(1))                             , eve::true_(eve::as<T>()) );
  TTS_EQUAL( (eve::true_(eve::as<T>()) != eve::true_(eve::as<T>())) , eve::false_(eve::as<T>()));
  TTS_EQUAL( (eve::true_(eve::as<T>()) != eve::false_(eve::as<T>())), eve::true_(eve::as<T>()) );

  eve::logical<T> mixed1([](auto i, auto) { return i%3 == 0; });
  eve::logical<T> mixed2([](auto i, auto) { return i%2 == 0; });
  eve::logical<T> ref([mixed1,mixed2](auto i, auto) { return mixed1.get(i) != mixed2.get(i); });

  TTS_EQUAL( (mixed1 != mixed2), ref);
}
