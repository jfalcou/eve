//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_and.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::logical_and return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::logical_and(eve::logical<T>(), eve::logical<T>()), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<v_t>(), eve::logical<T>())  , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<T>()  , eve::logical<v_t>()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::logical_and behavior on logicals", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_and(eve::false_(eve::as<T>()) , eve::false_(eve::as<T>())) , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(eve::false_(eve::as<T>()) , eve::true_(eve::as<T>()) ) , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(eve::true_(eve::as<T>())  , eve::true_(eve::as<T>()) ) , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_and(eve::true_(eve::as<T>())  , eve::false_(eve::as<T>())) , eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::logical_and(eve::false_(eve::as<v_t>()), eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(eve::false_(eve::as<v_t>()), eve::true_(eve::as<T>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(eve::true_(eve::as<v_t>()) , eve::true_(eve::as<T>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_and(eve::true_(eve::as<v_t>()) , eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::logical_and(eve::false_(eve::as<T>()) , eve::false_(eve::as<v_t>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(eve::false_(eve::as<T>()) , eve::true_(eve::as<v_t>())  ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(eve::true_(eve::as<T>())  , eve::true_(eve::as<v_t>())  ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_and(eve::true_(eve::as<T>())  , eve::false_(eve::as<v_t>()) ), eve::false_(eve::as<T>()));
}
