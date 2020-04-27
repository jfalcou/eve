//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_notor.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::logical_notor return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_notor(T()         , T())         ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(logical<T>(), T())         ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(logical<T>(), logical<T>())), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(T()         , logical<T>())), (logical<T>));

  TTS_EXPR_IS((eve::logical_notor(v_t()         , T())           ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(T()          , v_t())          ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(logical<T>() , v_t())          ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(logical<v_t>(), T())           ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(logical<v_t>(), logical<T>())  ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(logical<T>() , logical<v_t>()) ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(v_t()         , logical<T>())  ), (logical<T>));
  TTS_EXPR_IS((eve::logical_notor(T()          , logical<v_t>()) ), (logical<T>));
}

TTS_CASE_TPL("Check eve::logical_notor behavior on scalars", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_notor((T(0)), (T(0))), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor((T(0)), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor((T(2)), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor((T(1)), (T(0))), eve::False<T>());

  TTS_EQUAL(eve::logical_notor(v_t(0), (T(0))), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(v_t(0), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(v_t(2), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(v_t(1), (T(0))), eve::False<T>());

  TTS_EQUAL(eve::logical_notor((T(0)), v_t(0)), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor((T(0)), v_t(1)), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor((T(2)), v_t(1)), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor((T(1)), v_t(0)), eve::False<T>());

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::detail::as_integer_t<T>;
    TTS_EQUAL(eve::logical_notor((i_t(0)), (T(0))), eve::True<i_t>());
    TTS_EQUAL(eve::logical_notor((i_t(0)), (T(1))), eve::True<i_t>());
    TTS_EQUAL(eve::logical_notor((i_t(2)), (T(1))), eve::True<i_t>() );
    TTS_EQUAL(eve::logical_notor((i_t(1)), (T(0))), eve::False<i_t>());

    TTS_EQUAL(eve::logical_notor((T(0)), i_t(0)), eve::True<T>());
    TTS_EQUAL(eve::logical_notor((T(0)), i_t(1)), eve::True<T>());
    TTS_EQUAL(eve::logical_notor((T(2)), i_t(1)), eve::True<T>() );
    TTS_EQUAL(eve::logical_notor((T(1)), i_t(0)), eve::False<T>());
  }
}

TTS_CASE_TPL("Check eve::logical_notor behavior on logicals", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_notor(eve::False<T>() , eve::False<T>()) , eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::False<T>() , eve::True<T>() ) , eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::True<T>()  , eve::True<T>() ) , eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::True<T>()  , eve::False<T>()) , eve::False<T>());

  TTS_EQUAL(eve::logical_notor(eve::False<v_t>(), eve::False<T>()), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::False<v_t>(), eve::True<T>() ), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::True<v_t>() , eve::True<T>() ), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::True<v_t>() , eve::False<T>()), eve::False<T>());

  TTS_EQUAL(eve::logical_notor(eve::False<T>() , eve::False<v_t>() ), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::False<T>() , eve::True<v_t>()  ), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::True<T>()  , eve::True<v_t>()  ), eve::True<T>() );
  TTS_EQUAL(eve::logical_notor(eve::True<T>()  , eve::False<v_t>() ), eve::False<T>());
}
