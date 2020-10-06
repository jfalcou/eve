//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_lessgreater.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE("Check eve::is_lessgreater return type")
{
  TTS_EXPR_IS(eve::is_lessgreater(EVE_TYPE()  , EVE_TYPE()  ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::is_lessgreater(EVE_TYPE()  , EVE_VALUE() ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::is_lessgreater(EVE_VALUE() , EVE_TYPE()  ), eve::logical<EVE_TYPE>);
}

TTS_CASE_TPL("Check eve::is_lessgreater behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_lessgreater(T(1)         , eve::nan(eve::as<T>())), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::is_lessgreater(eve::nan(eve::as<T>()), T(1)         ), eve::false_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_lessgreater(  T(1),   T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_lessgreater(  T(1), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_lessgreater(v_t(1),   T(1)), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::is_lessgreater(  T(3),   T(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_lessgreater(  T(3), v_t(1)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_lessgreater(v_t(3),   T(1)), eve::true_(eve::as<T>()));

  TTS_EQUAL(eve::is_lessgreater(  T(1),   T(3)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_lessgreater(  T(1), v_t(3)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_lessgreater(v_t(1),   T(3)), eve::true_(eve::as<T>()));
}
