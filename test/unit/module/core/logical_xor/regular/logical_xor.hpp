//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_xor.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

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
  TTS_EQUAL(eve::logical_xor(T(0), T(0)), eve::False(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(T(0), T(1)), eve::True<T>()  );
  TTS_EQUAL(eve::logical_xor(T(2), T(1)), eve::False(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(T(1), T(0)), eve::True<T>()  );

  TTS_EQUAL(eve::logical_xor(v_t(0), T(0)), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(v_t(0), T(1)), eve::True<T>() );
  TTS_EQUAL(eve::logical_xor(v_t(2), T(1)), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(v_t(1), T(0)), eve::True<T>() );

  TTS_EQUAL(eve::logical_xor(T(0), v_t(0)), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(T(0), v_t(1)), eve::True<T>() );
  TTS_EQUAL(eve::logical_xor(T(2), v_t(1)), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(T(1), v_t(0)), eve::True<T>() );

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::detail::as_integer_t<T>;
    TTS_EQUAL(eve::logical_xor(i_t(0), T(0)), eve::False(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_xor(i_t(0), T(1)), eve::True<i_t>()  );
    TTS_EQUAL(eve::logical_xor(i_t(2), T(1)), eve::False(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_xor(i_t(1), T(0)), eve::True<i_t>()  );

    TTS_EQUAL(eve::logical_xor(T(0), i_t(0)), eve::False(eve::as<T>()) );
    TTS_EQUAL(eve::logical_xor(T(0), i_t(1)), eve::True<T>()  );
    TTS_EQUAL(eve::logical_xor(T(2), i_t(1)), eve::False(eve::as<T>()) );
    TTS_EQUAL(eve::logical_xor(T(1), i_t(0)), eve::True<T>()  );
  }
}

TTS_CASE_TPL("Check eve::logical_xor behavior on logicals", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::logical_xor(eve::False(eve::as<T>()) , eve::False(eve::as<T>())) , eve::False(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(eve::False(eve::as<T>()) , eve::True<T>() ) , eve::True<T>()  );
  TTS_EQUAL(eve::logical_xor(eve::True<T>()  , eve::True<T>() ) , eve::False(eve::as<T>()) );
  TTS_EQUAL(eve::logical_xor(eve::True<T>()  , eve::False(eve::as<T>())) , eve::True<T>()  );

  TTS_EQUAL(eve::logical_xor(eve::False(eve::as<v_t>()), eve::False(eve::as<T>())), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::False(eve::as<v_t>()), eve::True<T>() ), eve::True<T>() );
  TTS_EQUAL(eve::logical_xor(eve::True<v_t>() , eve::True<T>() ), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::True<v_t>() , eve::False(eve::as<T>())), eve::True<T>() );

  TTS_EQUAL(eve::logical_xor(eve::False(eve::as<T>()) , eve::False(eve::as<v_t>()) ), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::False(eve::as<T>()) , eve::True<v_t>()  ), eve::True<T>() );
  TTS_EQUAL(eve::logical_xor(eve::True<T>()  , eve::True<v_t>()  ), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::logical_xor(eve::True<T>()  , eve::False(eve::as<v_t>()) ), eve::True<T>() );
}
