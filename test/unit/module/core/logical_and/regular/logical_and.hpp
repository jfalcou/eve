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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

//#ifdef  EVE_SIMD_TESTS
// // TTS_CASE_TPL("Check extra cases", EVE_TYPE)
// // {
// //   using eve::logical;

// //   using i_t = logical<eve::as_wide_t<int, eve::fixed<4>>>;
// //   using j_t = logical<eve::as_wide_t<double, eve::fixed<4>>>;
// //   using k_t = logical<eve::as_wide_t<double, eve::cardinal_t<T>>>;
// //   TTS_EXPR_IS((eve::logical_and(j_t()         , i_t())), (j_t));
// //   TTS_EXPR_IS((eve::logical_and(j_t()         , int())) , (j_t));
// //   TTS_EXPR_IS((eve::logical_and(int(), j_t())), (i_t));
// //   TTS_EXPR_IS((eve::logical_and(logical<T>()         , k_t())), (logical<T>));
// //   TTS_EXPR_IS((eve::logical_and(v_t()        , i_t())         ), (logical<eve::as_wide_t<v_t,eve::fixed<4>>>));
// //   TTS_EQUAL(1, 1);
// // }

// TTS_CASE_TPL("Check  extra cases", EVE_TYPE)
// {
//   using eve::logical;

//   using i_t = logical<eve::as_wide_t<int, eve::fixed<4>>>;
//   using j_t = logical<eve::as_wide_t<double, eve::fixed<4>>>;
//   TTS_EQUAL(eve::logical_and((j_t(0)), (i_t(0))), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(0)), (i_t(1))), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(2)), (i_t(1))), eve::True<j_t>() );
//   TTS_EQUAL(eve::logical_and((j_t(1)), (i_t(0))), eve::False<j_t>());

//   TTS_EQUAL(eve::logical_and(int(0), (j_t(0))), eve::False<i_t>());
//   TTS_EQUAL(eve::logical_and(int(0), (j_t(1))), eve::False<i_t>());
//   TTS_EQUAL(eve::logical_and(int(2), (j_t(1))), eve::True<i_t>() );
//   TTS_EQUAL(eve::logical_and(int(1), (j_t(0))), eve::False<i_t>());

//   TTS_EQUAL(eve::logical_and((j_t(0)), int(0)), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(0)), int(1)), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(2)), int(1)), eve::True<j_t>() );
//   TTS_EQUAL(eve::logical_and((j_t(1)), int(0)), eve::False<j_t>());
// }
//#endif

TTS_CASE_TPL("Check eve::logical_and return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_and(T()         , T())         ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(logical<T>(), T())         ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(logical<T>(), logical<T>())), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(T()         , logical<T>())), (logical<T>));

  TTS_EXPR_IS((eve::logical_and(v_t()         , T())           ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(T()          , v_t())          ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(logical<T>() , v_t())          ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(logical<v_t>(), T())           ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(logical<v_t>(), logical<T>())  ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(logical<T>() , logical<v_t>()) ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(v_t()         , logical<T>())  ), (logical<T>));
  TTS_EXPR_IS((eve::logical_and(T()          , logical<v_t>()) ), (logical<T>));
}

TTS_CASE_TPL("Check eve::operator&& return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS((logical<T>()  && T()         ), (logical<T>));
  TTS_EXPR_IS((logical<T>()  && logical<T>()), (logical<T>));
  TTS_EXPR_IS((T()           && logical<T>()), (logical<T>));
  TTS_EXPR_IS((logical<T>()  && v_t()        ), (logical<T>));
  TTS_EXPR_IS((logical<v_t>() && T()         ), (logical<T>));
}

TTS_CASE_TPL("Check eve::logical_and behavior on numbers", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_and((T(0)), (T(0))), eve::False<T>());
  TTS_EQUAL(eve::logical_and((T(0)), (T(1))), eve::False<T>());
  TTS_EQUAL(eve::logical_and((T(2)), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_and((T(1)), (T(0))), eve::False<T>());

  TTS_EQUAL(eve::logical_and(v_t(0), (T(0))), eve::False<T>());
  TTS_EQUAL(eve::logical_and(v_t(0), (T(1))), eve::False<T>());
  TTS_EQUAL(eve::logical_and(v_t(2), (T(1))), eve::True<T>() );
  TTS_EQUAL(eve::logical_and(v_t(1), (T(0))), eve::False<T>());

  TTS_EQUAL(eve::logical_and((T(0)), v_t(0)), eve::False<T>());
  TTS_EQUAL(eve::logical_and((T(0)), v_t(1)), eve::False<T>());
  TTS_EQUAL(eve::logical_and((T(2)), v_t(1)), eve::True<T>() );
  TTS_EQUAL(eve::logical_and((T(1)), v_t(0)), eve::False<T>());

  if constexpr(eve::floating_value<T>)
  {
    using i_t = eve::detail::as_integer_t<T>;
    TTS_EQUAL(eve::logical_and((i_t(0)), (T(0))), eve::False<i_t>());
    TTS_EQUAL(eve::logical_and((i_t(0)), (T(1))), eve::False<i_t>());
    TTS_EQUAL(eve::logical_and((i_t(2)), (T(1))), eve::True<i_t>() );
    TTS_EQUAL(eve::logical_and((i_t(1)), (T(0))), eve::False<i_t>());

    TTS_EQUAL(eve::logical_and((T(0)), i_t(0)), eve::False<T>());
    TTS_EQUAL(eve::logical_and((T(0)), i_t(1)), eve::False<T>());
    TTS_EQUAL(eve::logical_and((T(2)), i_t(1)), eve::True<T>() );
    TTS_EQUAL(eve::logical_and((T(1)), i_t(0)), eve::False<T>());
  }
}


TTS_CASE_TPL("Check eve::logical_and behavior on logicals", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_and(eve::False<T>() , eve::False<T>()) , eve::False<T>());
  TTS_EQUAL(eve::logical_and(eve::False<T>() , eve::True<T>() ) , eve::False<T>());
  TTS_EQUAL(eve::logical_and(eve::True<T>()  , eve::True<T>() ) , eve::True<T>() );
  TTS_EQUAL(eve::logical_and(eve::True<T>()  , eve::False<T>()) , eve::False<T>());

  TTS_EQUAL(eve::logical_and(eve::False<v_t>(), eve::False<T>()), eve::False<T>());
  TTS_EQUAL(eve::logical_and(eve::False<v_t>(), eve::True<T>() ), eve::False<T>());
  TTS_EQUAL(eve::logical_and(eve::True<v_t>() , eve::True<T>() ), eve::True<T>() );
  TTS_EQUAL(eve::logical_and(eve::True<v_t>() , eve::False<T>()), eve::False<T>());

  TTS_EQUAL(eve::logical_and(eve::False<T>() , eve::False<v_t>() ), eve::False<T>());
  TTS_EQUAL(eve::logical_and(eve::False<T>() , eve::True<v_t>()  ), eve::False<T>());
  TTS_EQUAL(eve::logical_and(eve::True<T>()  , eve::True<v_t>()  ), eve::True<T>() );
  TTS_EQUAL(eve::logical_and(eve::True<T>()  , eve::False<v_t>() ), eve::False<T>());
}

TTS_CASE_TPL("Check eve::operator&& behavior on logicals", EVE_TYPE)
{
  TTS_EQUAL(eve::False<T>()  && eve::False<T>(), eve::False<T>());
  TTS_EQUAL(eve::False<T>()  && eve::True<T>() , eve::False<T>());
  TTS_EQUAL(eve::True<T>()   && eve::True<T>() , eve::True<T>() );
  TTS_EQUAL(eve::True<T>()   && eve::False<T>(), eve::False<T>());

  TTS_EQUAL(eve::False<v_t>() && eve::False<T>(), eve::False<T>());
  TTS_EQUAL(eve::False<v_t>() && eve::True<T>() , eve::False<T>());
  TTS_EQUAL(eve::True<v_t>()  && eve::True<T>() , eve::True<T>() );
  TTS_EQUAL(eve::True<v_t>()  && eve::False<T>(), eve::False<T>());

  TTS_EQUAL(eve::False<T>()  && eve::False<v_t>(), eve::False<T>());
  TTS_EQUAL(eve::False<T>()  && eve::True<v_t>() , eve::False<T>());
  TTS_EQUAL(eve::True<T>()   && eve::True<v_t>() , eve::True<T>() );
  TTS_EQUAL(eve::True<T>()   && eve::False<v_t>(), eve::False<T>());
}
