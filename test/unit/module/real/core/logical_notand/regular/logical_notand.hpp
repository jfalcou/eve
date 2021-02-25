//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_notand.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::logical_notand return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::logical_notand(T()              , T())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(eve::logical<T>(), T())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(eve::logical<T>(), eve::logical<T>()), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(T()              , eve::logical<T>()), eve::logical<T>);

  TTS_EXPR_IS(eve::logical_notand(v_t()               , T())                , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(T()                 , v_t())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(eve::logical<T>()   , v_t())              , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(eve::logical<v_t>() , T())                , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(eve::logical<v_t>() , eve::logical<T>())  , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(eve::logical<T>()   , eve::logical<v_t>()), eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(v_t()               , eve::logical<T>())  , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_notand(T()                 , eve::logical<v_t>()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::logical_notand behavior on scalars", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_notand(T(0), T(0)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(T(0), T(1)), eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::logical_notand(T(2), T(1)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(T(1), T(0)), eve::false_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_notand(v_t(0), T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(v_t(0), T(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(v_t(2), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(v_t(1), T(0)), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::logical_notand(T(0), v_t(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(T(0), v_t(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(T(2), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(T(1), v_t(0)), eve::false_(eve::as<T>()));

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::as_integer_t<T>;
    TTS_EQUAL(eve::logical_notand(i_t(0), T(0)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_notand(i_t(0), T(1)), eve::true_(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_notand(i_t(2), T(1)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_notand(i_t(1), T(0)), eve::false_(eve::as<i_t>()));

    TTS_EQUAL(eve::logical_notand(T(0), i_t(0)), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::logical_notand(T(0), i_t(1)), eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::logical_notand(T(2), i_t(1)), eve::false_(eve::as<T>()));
    TTS_EQUAL(eve::logical_notand(T(1), i_t(0)), eve::false_(eve::as<T>()));
  }
}

TTS_CASE_TPL("Check eve::logical_notand behavior on logicals", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_notand(eve::false_(eve::as<T>()) , eve::false_(eve::as<T>())) , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(eve::false_(eve::as<T>()) , eve::true_(eve::as<T>()) ) , eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::logical_notand(eve::true_(eve::as<T>())  , eve::true_(eve::as<T>()) ) , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(eve::true_(eve::as<T>())  , eve::false_(eve::as<T>())) , eve::false_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_notand(eve::false_(eve::as<v_t>()), eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(eve::false_(eve::as<v_t>()), eve::true_(eve::as<T>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(eve::true_(eve::as<v_t>()) , eve::true_(eve::as<T>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(eve::true_(eve::as<v_t>()) , eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));

  TTS_EQUAL(eve::logical_notand(eve::false_(eve::as<T>()) , eve::false_(eve::as<v_t>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(eve::false_(eve::as<T>()) , eve::true_(eve::as<v_t>())  ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_notand(eve::true_(eve::as<T>())  , eve::true_(eve::as<v_t>())  ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_notand(eve::true_(eve::as<T>())  , eve::false_(eve::as<v_t>()) ), eve::false_(eve::as<T>()));
}
