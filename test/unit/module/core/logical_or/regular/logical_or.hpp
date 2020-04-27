//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_or.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/traits.hpp>
#include <eve/arch/abi_of.hpp>

TTS_CASE_TPL("Check eve::logical_or return type", EVE_TYPE)
{
  using eve::logical;
  TTS_EXPR_IS((eve::logical_or(T()         , T())         ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(logical<T>(), T())         ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(logical<T>(), logical<T>())), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(T()         , logical<T>())), (logical<T>));

  TTS_EXPR_IS((eve::logical_or(v_t()         , T())           ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(T()          , v_t())          ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(logical<T>() , v_t())          ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(logical<v_t>(), T())           ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(logical<v_t>(), logical<T>())  ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(logical<T>() , logical<v_t>()) ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(v_t()         , logical<T>())  ), (logical<T>));
  TTS_EXPR_IS((eve::logical_or(T()          , logical<v_t>()) ), (logical<T>));
}

TTS_CASE_TPL("Check eve::operator|| return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS((logical<T>()  || T()         ), (logical<T>));
  TTS_EXPR_IS((logical<T>()  || logical<T>()), (logical<T>));
  TTS_EXPR_IS((T()           || logical<T>()), (logical<T>));
  TTS_EXPR_IS((logical<T>()  || v_t()        ), (logical<T>));
  TTS_EXPR_IS((logical<v_t>() || T()         ), (logical<T>));
}

TTS_CASE_TPL("Check eve::logical_or behavior on scalars", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_or((T(0)), (T(0))), eve::False<T>() );
  TTS_EQUAL(eve::logical_or((T(0)), (T(1))), eve::True<T>()  );
  TTS_EQUAL(eve::logical_or((T(2)), (T(1))), eve::True<T>()  );
  TTS_EQUAL(eve::logical_or((T(1)), (T(0))), eve::True<T>()  );

  TTS_EQUAL(eve::logical_or(v_t(0), (T(0))), eve::False<T>());
  TTS_EQUAL(eve::logical_or(v_t(0), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_or(v_t(2), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_or(v_t(1), (T(0))), eve::True<T>() );

  TTS_EQUAL(eve::logical_or((T(0)), v_t(0)), eve::False<T>());
  TTS_EQUAL(eve::logical_or((T(0)), v_t(1)), eve::True<T>() );
  TTS_EQUAL(eve::logical_or((T(2)), v_t(1)), eve::True<T>() );
  TTS_EQUAL(eve::logical_or((T(1)), v_t(0)), eve::True<T>() );

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::detail::as_integer_t<T>;
    TTS_EQUAL(eve::logical_or((i_t(0)), (T(0))), eve::False<i_t>());
    TTS_EQUAL(eve::logical_or((i_t(0)), (T(1))), eve::True<i_t>());
    TTS_EQUAL(eve::logical_or((i_t(2)), (T(1))), eve::True<i_t>() );
    TTS_EQUAL(eve::logical_or((i_t(1)), (T(0))), eve::True<i_t>());

    TTS_EQUAL(eve::logical_or((T(0)), i_t(0)), eve::False<T>());
    TTS_EQUAL(eve::logical_or((T(0)), i_t(1)), eve::True<T>());
    TTS_EQUAL(eve::logical_or((T(2)), i_t(1)), eve::True<T>() );
    TTS_EQUAL(eve::logical_or((T(1)), i_t(0)), eve::True<T>());
  }
}

TTS_CASE_TPL("Check eve::logical_or behavior on logicals", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_or(eve::False<T>() , eve::False<T>()) , eve::False<T>() );
  TTS_EQUAL(eve::logical_or(eve::False<T>() , eve::True<T>() ) , eve::True<T>()  );
  TTS_EQUAL(eve::logical_or(eve::True<T>()  , eve::True<T>() ) , eve::True<T>()  );
  TTS_EQUAL(eve::logical_or(eve::True<T>()  , eve::False<T>()) , eve::True<T>()  );

  TTS_EQUAL(eve::logical_or(eve::False<v_t>(), eve::False<T>()), eve::False<T>());
  TTS_EQUAL(eve::logical_or(eve::False<v_t>(), eve::True<T>() ), eve::True<T>() );
  TTS_EQUAL(eve::logical_or(eve::True<v_t>() , eve::True<T>() ), eve::True<T>() );
  TTS_EQUAL(eve::logical_or(eve::True<v_t>() , eve::False<T>()), eve::True<T>() );

  TTS_EQUAL(eve::logical_or(eve::False<T>() , eve::False<v_t>() ), eve::False<T>());
  TTS_EQUAL(eve::logical_or(eve::False<T>() , eve::True<v_t>()  ), eve::True<T>() );
  TTS_EQUAL(eve::logical_or(eve::True<T>()  , eve::True<v_t>()  ), eve::True<T>() );
  TTS_EQUAL(eve::logical_or(eve::True<T>()  , eve::False<v_t>() ), eve::True<T>() );
}

TTS_CASE_TPL("Check eve::operator|| behavior on logicals", EVE_TYPE)
{
  TTS_EQUAL(eve::False<T>()  || eve::False<T>(), eve::False<T>() );
  TTS_EQUAL(eve::False<T>()  || eve::True<T>() , eve::True<T>()  );
  TTS_EQUAL(eve::True<T>()   || eve::True<T>() , eve::True<T>()  );
  TTS_EQUAL(eve::True<T>()   || eve::False<T>(), eve::True<T>()  );

  TTS_EQUAL(eve::False<v_t>() || eve::False<T>(), eve::False<T>() );
  TTS_EQUAL(eve::False<v_t>() || eve::True<T>() , eve::True<T>()  );
  TTS_EQUAL(eve::True<v_t>()  || eve::True<T>() , eve::True<T>()  );
  TTS_EQUAL(eve::True<v_t>()  || eve::False<T>(), eve::True<T>()  );

  TTS_EQUAL(eve::False<T>()  || eve::False<v_t>(), eve::False<T>());
  TTS_EQUAL(eve::False<T>()  || eve::True<v_t>() , eve::True<T>() );
  TTS_EQUAL(eve::True<T>()   || eve::True<v_t>() , eve::True<T>() );
  TTS_EQUAL(eve::True<T>()   || eve::False<v_t>(), eve::True<T>() );
}
