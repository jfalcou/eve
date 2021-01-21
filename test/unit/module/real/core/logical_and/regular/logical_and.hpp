//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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

TTS_CASE_TPL("Check eve::operator&& return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::logical<T>()    &&  eve::logical<T>()   , eve::logical<T>);
  TTS_EXPR_IS( eve::logical<v_t>()  &&  eve::logical<T>()   , eve::logical<T>);
  TTS_EXPR_IS( eve::logical<T>()    &&  eve::logical<v_t>() , eve::logical<T>);
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

TTS_CASE_TPL("Check eve::operator&& behavior on logicals", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL((eve::false_(eve::as<T>())  && eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));
  TTS_EQUAL((eve::false_(eve::as<T>())  && eve::true_(eve::as<T>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL((eve::true_(eve::as<T>())   && eve::true_(eve::as<T>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL((eve::true_(eve::as<T>())   && eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));

  TTS_EQUAL((eve::false_(eve::as<v_t>()) && eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));
  TTS_EQUAL((eve::false_(eve::as<v_t>()) && eve::true_(eve::as<T>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL((eve::true_(eve::as<v_t>())  && eve::true_(eve::as<T>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL((eve::true_(eve::as<v_t>())  && eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));

  TTS_EQUAL((eve::false_(eve::as<T>())  && eve::false_(eve::as<v_t>())), eve::false_(eve::as<T>()));
  TTS_EQUAL((eve::false_(eve::as<T>())  && eve::true_(eve::as<v_t>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL((eve::true_(eve::as<T>())   && eve::true_(eve::as<v_t>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL((eve::true_(eve::as<T>())   && eve::false_(eve::as<v_t>())), eve::false_(eve::as<T>()));
}
