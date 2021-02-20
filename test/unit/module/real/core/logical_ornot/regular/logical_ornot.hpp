//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_ornot.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::logical_ornot return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::logical_ornot(T()              , T()               ), eve::logical<T> );
  TTS_EXPR_IS(eve::logical_ornot(eve::logical<T>(), T()               ), eve::logical<T> );
  TTS_EXPR_IS(eve::logical_ornot(eve::logical<T>(), eve::logical<T>() ), eve::logical<T> );
  TTS_EXPR_IS(eve::logical_ornot(T()              , eve::logical<T>() ), eve::logical<T> );

  TTS_EXPR_IS(eve::logical_ornot(v_t()              , T()                 ), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_ornot(T()                , v_t()               ), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_ornot(eve::logical<T>()  , v_t()               ), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_ornot(eve::logical<v_t>(), T()                 ), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_ornot(eve::logical<v_t>(), eve::logical<T>()   ), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_ornot(eve::logical<T>()  , eve::logical<v_t>() ), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_ornot(v_t()              , eve::logical<T>()   ), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_ornot(T()                , eve::logical<v_t>() ), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::logical_ornot behavior on scalars", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_ornot(T(0), T(0)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(T(0), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_ornot(T(2), T(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(T(1), T(0)), eve::true_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_ornot(v_t(0), T(0)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(v_t(0), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_ornot(v_t(2), T(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(v_t(1), T(0)), eve::true_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_ornot(T(0), v_t(0)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(T(0), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_ornot(T(2), v_t(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(T(1), v_t(0)), eve::true_(eve::as<T>()) );
  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::as_integer_t<T>;
    TTS_EQUAL(eve::logical_ornot(i_t(0), T(0)), eve::true_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_ornot(i_t(0), T(1)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_ornot(i_t(2), T(1)), eve::true_(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_ornot(i_t(1), T(0)), eve::true_(eve::as<i_t>()));

    TTS_EQUAL(eve::logical_ornot(T(0), i_t(0)), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::logical_ornot(T(0), i_t(1)), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::logical_ornot(T(2), i_t(1)), eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::logical_ornot(T(1), i_t(0)), eve::true_(eve::as<T>()));
  }
}

TTS_CASE_TPL("Check eve::logical_ornot behavior on logicals", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_ornot(eve::false_(eve::as<T>()) , eve::false_(eve::as<T>())) , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(eve::false_(eve::as<T>()) , eve::true_(eve::as<T>()) ) , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_ornot(eve::true_(eve::as<T>())  , eve::true_(eve::as<T>()) ) , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(eve::true_(eve::as<T>())  , eve::false_(eve::as<T>())) , eve::true_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_ornot(eve::false_(eve::as<v_t>()), eve::false_(eve::as<T>())), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(eve::false_(eve::as<v_t>()), eve::true_(eve::as<T>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_ornot(eve::true_(eve::as<v_t>()) , eve::true_(eve::as<T>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(eve::true_(eve::as<v_t>()) , eve::false_(eve::as<T>())), eve::true_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_ornot(eve::false_(eve::as<T>()) , eve::false_(eve::as<v_t>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(eve::false_(eve::as<T>()) , eve::true_(eve::as<v_t>())  ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_ornot(eve::true_(eve::as<T>())  , eve::true_(eve::as<v_t>())  ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_ornot(eve::true_(eve::as<T>())  , eve::false_(eve::as<v_t>()) ), eve::true_(eve::as<T>()) );
}
