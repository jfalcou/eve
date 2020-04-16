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
// TTS_CASE("Check extra cases")
// {
//   using eve::logical;

//   using i_t = logical<eve::as_wide_t<int, eve::fixed<4>>>;
//   using j_t = logical<eve::as_wide_t<double, eve::fixed<4>>>;
//   using k_t = logical<eve::as_wide_t<double, eve::cardinal_t<EVE_TYPE>>>;
//   TTS_EXPR_IS((eve::logical_and(j_t()         , i_t())), (j_t));
//   TTS_EXPR_IS((eve::logical_and(j_t()         , int())) , (j_t));
//   TTS_EXPR_IS((eve::logical_and(int(), j_t())), (i_t));
//   TTS_EXPR_IS((eve::logical_and(logical<EVE_TYPE>()         , k_t())), (logical<EVE_TYPE>));
//   TTS_EXPR_IS((eve::logical_and(EVE_VALUE()        , i_t())         ), (logical<eve::as_wide_t<EVE_VALUE,eve::fixed<4>>>));
//   TTS_EQUAL(1, 1);
// }

// TTS_CASE("Check  extra cases")
// {
//   using eve::logical;

//   using i_t = logical<eve::as_wide_t<int, eve::fixed<4>>>;
//   using j_t = logical<eve::as_wide_t<double, eve::fixed<4>>>;
//   TTS_EQUAL(eve::logical_and((j_t(0)), (j_t(0))), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(0)), (j_t(1))), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(2)), (j_t(1))), eve::True<j_t>() );
//   TTS_EQUAL(eve::logical_and((j_t(1)), (j_t(0))), eve::False<j_t>());

//   TTS_EQUAL(eve::logical_and(int(0), (j_t(0))), eve::False<i_t>());
//   TTS_EQUAL(eve::logical_and(int(0), (j_t(1))), eve::False<i_t>());
//   TTS_EQUAL(eve::logical_and(int(2), (j_t(1))), eve::True<i_t>() );
//   TTS_EQUAL(eve::logical_and(int(1), (j_t(0))), eve::False<i_t>());

//   TTS_EQUAL(eve::logical_and((j_t(0)), int(0)), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(0)), int(1)), eve::False<j_t>());
//   TTS_EQUAL(eve::logical_and((j_t(2)), int(1)), eve::True<j_t>() );
//   TTS_EQUAL(eve::logical_and((j_t(1)), int(0)), eve::False<j_t>());
// }
// #endif

TTS_CASE("Check eve::logical_and return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_and(EVE_TYPE()         , EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(logical<EVE_TYPE>(), EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(logical<EVE_TYPE>(), logical<EVE_TYPE>())), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(EVE_TYPE()         , logical<EVE_TYPE>())), (logical<EVE_TYPE>));

  TTS_EXPR_IS((eve::logical_and(EVE_VALUE()         , EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(EVE_TYPE()          , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(logical<EVE_TYPE>() , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(logical<EVE_VALUE>(), EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(logical<EVE_VALUE>(), logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(logical<EVE_TYPE>() , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(EVE_VALUE()         , logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_and(EVE_TYPE()          , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::operator&& return type")
{
  using eve::logical;

  TTS_EXPR_IS((logical<EVE_TYPE>()  && EVE_TYPE()         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((logical<EVE_TYPE>()  && logical<EVE_TYPE>()), (logical<EVE_TYPE>));
  TTS_EXPR_IS((EVE_TYPE()           && logical<EVE_TYPE>()), (logical<EVE_TYPE>));
  TTS_EXPR_IS((logical<EVE_TYPE>()  && EVE_VALUE()        ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((logical<EVE_VALUE>() && EVE_TYPE()         ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::logical_and behavior on numbers")
{
  TTS_EQUAL(eve::logical_and((EVE_TYPE(0)), (EVE_TYPE(0))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and((EVE_TYPE(0)), (EVE_TYPE(1))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and((EVE_TYPE(2)), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_and((EVE_TYPE(1)), (EVE_TYPE(0))), eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::logical_and(EVE_VALUE(0), (EVE_TYPE(0))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(EVE_VALUE(0), (EVE_TYPE(1))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(EVE_VALUE(2), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_and(EVE_VALUE(1), (EVE_TYPE(0))), eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::logical_and((EVE_TYPE(0)), EVE_VALUE(0)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and((EVE_TYPE(0)), EVE_VALUE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and((EVE_TYPE(2)), EVE_VALUE(1)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_and((EVE_TYPE(1)), EVE_VALUE(0)), eve::False<EVE_TYPE>());

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    using i_t = eve::detail::as_integer_t<EVE_TYPE>;
    TTS_EQUAL(eve::logical_and((i_t(0)), (EVE_TYPE(0))), eve::False<i_t>());
    TTS_EQUAL(eve::logical_and((i_t(0)), (EVE_TYPE(1))), eve::False<i_t>());
    TTS_EQUAL(eve::logical_and((i_t(2)), (EVE_TYPE(1))), eve::True<i_t>() );
    TTS_EQUAL(eve::logical_and((i_t(1)), (EVE_TYPE(0))), eve::False<i_t>());

    TTS_EQUAL(eve::logical_and((EVE_TYPE(0)), i_t(0)), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::logical_and((EVE_TYPE(0)), i_t(1)), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::logical_and((EVE_TYPE(2)), i_t(1)), eve::True<EVE_TYPE>() );
    TTS_EQUAL(eve::logical_and((EVE_TYPE(1)), i_t(0)), eve::False<EVE_TYPE>());
  }
}


TTS_CASE("Check eve::logical_and behavior on logicals")
{
  TTS_EQUAL(eve::logical_and(eve::False<EVE_TYPE>() , eve::False<EVE_TYPE>()) , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(eve::False<EVE_TYPE>() , eve::True<EVE_TYPE>() ) , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(eve::True<EVE_TYPE>()  , eve::True<EVE_TYPE>() ) , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_and(eve::True<EVE_TYPE>()  , eve::False<EVE_TYPE>()) , eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::logical_and(eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>()), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(eve::False<EVE_VALUE>(), eve::True<EVE_TYPE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_and(eve::True<EVE_VALUE>() , eve::False<EVE_TYPE>()), eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::logical_and(eve::False<EVE_TYPE>() , eve::False<EVE_VALUE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(eve::False<EVE_TYPE>() , eve::True<EVE_VALUE>()  ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_and(eve::True<EVE_TYPE>()  , eve::True<EVE_VALUE>()  ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_and(eve::True<EVE_TYPE>()  , eve::False<EVE_VALUE>() ), eve::False<EVE_TYPE>());
}

TTS_CASE("Check eve::operator&& behavior on logicals")
{
  TTS_EQUAL(eve::False<EVE_TYPE>()  && eve::False<EVE_TYPE>(), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::False<EVE_TYPE>()  && eve::True<EVE_TYPE>() , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::True<EVE_TYPE>()   && eve::True<EVE_TYPE>() , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::True<EVE_TYPE>()   && eve::False<EVE_TYPE>(), eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::False<EVE_VALUE>() && eve::False<EVE_TYPE>(), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::False<EVE_VALUE>() && eve::True<EVE_TYPE>() , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::True<EVE_VALUE>()  && eve::True<EVE_TYPE>() , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::True<EVE_VALUE>()  && eve::False<EVE_TYPE>(), eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::False<EVE_TYPE>()  && eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::False<EVE_TYPE>()  && eve::True<EVE_VALUE>() , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::True<EVE_TYPE>()   && eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::True<EVE_TYPE>()   && eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>());
}
