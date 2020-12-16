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

  TTS_EXPR_IS(eve::logical_and(T()              , T())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<T>(), T())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<T>(), eve::logical<T>()), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(T()              , eve::logical<T>()), eve::logical<T>);

  TTS_EXPR_IS(eve::logical_and(v_t()              , T())                , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(T()                , v_t())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<T>()  , v_t())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<v_t>(), T())                , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<v_t>(), eve::logical<T>())  , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(eve::logical<T>()  , eve::logical<v_t>()), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(v_t()              , eve::logical<T>())  , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_and(T()                , eve::logical<v_t>()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::operator&& return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS((eve::logical<T>()   && T()              ), eve::logical<T> );
  TTS_EXPR_IS((eve::logical<T>()   && eve::logical<T>()), eve::logical<T> );
  TTS_EXPR_IS((T()                 && eve::logical<T>()), eve::logical<T> );
  TTS_EXPR_IS((eve::logical<T>()   && v_t()            ), eve::logical<T> );
  TTS_EXPR_IS((eve::logical<v_t>() && T()              ), eve::logical<T> );
}

TTS_CASE_TPL("Check eve::logical_and behavior on numbers", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_and(T(0), T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(T(0), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(T(2), T(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_and(T(1), T(0)), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::logical_and(v_t(0), T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(v_t(0), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(v_t(2), T(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_and(v_t(1), T(0)), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::logical_and(T(0), v_t(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(T(0), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_and(T(2), v_t(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_and(T(1), v_t(0)), eve::false_(eve::as<T>()));

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::detail::as_integer_t<T>;
    TTS_EQUAL(eve::logical_and(i_t(0), T(0)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_and(i_t(0), T(1)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_and(i_t(2), T(1)), eve::true_(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_and(i_t(1), T(0)), eve::false_(eve::as<i_t>()));

    TTS_EQUAL(eve::logical_and(T(0), i_t(0)), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::logical_and(T(0), i_t(1)), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::logical_and(T(2), i_t(1)), eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::logical_and(T(1), i_t(0)), eve::false_(eve::as<T>()));
  }
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
