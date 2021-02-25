//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_xor.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::logical_xor return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::logical_xor(T()              , T()               ), eve::logical<T> );
  TTS_EXPR_IS(eve::logical_xor(eve::logical<T>(), T()               ), eve::logical<T> );
  TTS_EXPR_IS(eve::logical_xor(eve::logical<T>(), eve::logical<T>() ), eve::logical<T> );
  TTS_EXPR_IS(eve::logical_xor(T()              , eve::logical<T>() ), eve::logical<T> );

  TTS_EXPR_IS(eve::logical_xor(v_t()              , T()                 ) , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_xor(T()                , v_t()               ) , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_xor(eve::logical<T>()  , v_t()               ) , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_xor(eve::logical<v_t>(), T()                 ) , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_xor(eve::logical<v_t>(), eve::logical<T>()   ) , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_xor(eve::logical<T>()  , eve::logical<v_t>() ) , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_xor(v_t()              , eve::logical<T>()   ) , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_xor(T()                , eve::logical<v_t>() ) , eve::logical<T>);
}

TTS_CASE_TPL("Check eve::logical_xor behavior on scalars", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::logical_xor(T(0), T(0)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(T(0), T(1)), eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::logical_xor(T(2), T(1)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(T(1), T(0)), eve::true_(eve::as<T>())  );

  TTS_EQUAL(eve::logical_xor(v_t(0), T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(v_t(0), T(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(v_t(2), T(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(v_t(1), T(0)), eve::true_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_xor(T(0), v_t(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(T(0), v_t(1)), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(T(2), v_t(1)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(T(1), v_t(0)), eve::true_(eve::as<T>()) );

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::as_integer_t<T>;
    TTS_EQUAL(eve::logical_xor(i_t(0), T(0)), eve::false_(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_xor(i_t(0), T(1)), eve::true_(eve::as<i_t>())  );
    TTS_EQUAL(eve::logical_xor(i_t(2), T(1)), eve::false_(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_xor(i_t(1), T(0)), eve::true_(eve::as<i_t>())  );

    TTS_EQUAL(eve::logical_xor(T(0), i_t(0)), eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::logical_xor(T(0), i_t(1)), eve::true_(eve::as<T>())  );
    TTS_EQUAL(eve::logical_xor(T(2), i_t(1)), eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::logical_xor(T(1), i_t(0)), eve::true_(eve::as<T>())  );
  }
}

TTS_CASE_TPL("Check eve::logical_xor behavior on logicals", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::logical_xor(eve::false_(eve::as<T>()) , eve::false_(eve::as<T>())) , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(eve::false_(eve::as<T>()) , eve::true_(eve::as<T>()) ) , eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::logical_xor(eve::true_(eve::as<T>())  , eve::true_(eve::as<T>()) ) , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(eve::true_(eve::as<T>())  , eve::false_(eve::as<T>())) , eve::true_(eve::as<T>())  );

  TTS_EQUAL(eve::logical_xor(eve::false_(eve::as<v_t>()), eve::false_(eve::as<T>())), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::false_(eve::as<v_t>()), eve::true_(eve::as<T>()) ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(eve::true_(eve::as<v_t>()) , eve::true_(eve::as<T>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::true_(eve::as<v_t>()) , eve::false_(eve::as<T>())), eve::true_(eve::as<T>()) );

  TTS_EQUAL(eve::logical_xor(eve::false_(eve::as<T>()) , eve::false_(eve::as<v_t>()) ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::false_(eve::as<T>()) , eve::true_(eve::as<v_t>())  ), eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(eve::true_(eve::as<T>())  , eve::true_(eve::as<v_t>())  ), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::true_(eve::as<T>())  , eve::false_(eve::as<v_t>()) ), eve::true_(eve::as<T>()) );
}
