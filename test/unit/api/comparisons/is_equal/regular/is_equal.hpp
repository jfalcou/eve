//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/concept/value.hpp>
#include <eve/logical.hpp>

TTS_CASE_TPL("Check eve::operator== return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  TTS_EXPR_IS((  T() ==    T()), logical<T>);
  TTS_EXPR_IS((  T() ==  v_t()), logical<T>);
  TTS_EXPR_IS((v_t() ==    T()), logical<T>);

  TTS_EXPR_IS((logical<T>()    == logical<T>()  ), logical<T>);
  TTS_EXPR_IS((logical<T>()    == logical<v_t>()), logical<T>);
  TTS_EXPR_IS((logical<v_t>()  == logical<T>()  ), logical<T>);
}

TTS_CASE_TPL("Check eve::operator== behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL((eve::nan(eve::as<T>()) == eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
    TTS_EQUAL((eve::nan(eve::as<T>()) == T(4)                   ), eve::false_(eve::as<T>()));
    TTS_EQUAL((T(4)                   == eve::nan(eve::as<T>()) ), eve::false_(eve::as<T>()));
  }

  TTS_EQUAL((T(1)           == T(1)           ), eve::true_(eve::as<T>()) );
  TTS_EQUAL((T(1)           == v_t(1)         ), eve::true_(eve::as<T>()) );
  TTS_EQUAL((T(3)           == T(1)           ), eve::false_(eve::as<T>()));
  TTS_EQUAL((T(3)           == v_t(1)         ), eve::false_(eve::as<T>()));
  TTS_EQUAL((eve::true_(eve::as<T>()) == eve::true_(eve::as<T>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL((eve::true_(eve::as<T>()) == eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));

  logical<T> mixed1([](auto i, auto) { return i%3 == 0; });
  logical<T> mixed2([](auto i, auto) { return i%2 == 0; });
  logical<T> ref([mixed1,mixed2](auto i, auto) { return mixed1.get(i) == mixed2.get(i); });

  TTS_EQUAL( (mixed1 == mixed2), ref);
}
