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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::logical_ornot return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_ornot(EVE_TYPE()         , EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(logical<EVE_TYPE>(), EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(logical<EVE_TYPE>(), logical<EVE_TYPE>())), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(EVE_TYPE()         , logical<EVE_TYPE>())), (logical<EVE_TYPE>));

  TTS_EXPR_IS((eve::logical_ornot(EVE_VALUE()         , EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(EVE_TYPE()          , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(logical<EVE_TYPE>() , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(logical<EVE_VALUE>(), EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(logical<EVE_VALUE>(), logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(logical<EVE_TYPE>() , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(EVE_VALUE()         , logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_ornot(EVE_TYPE()          , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::logical_ornot behavior on scalars")
{
  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(0)), (EVE_TYPE(0))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(0)), (EVE_TYPE(1))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(2)), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(1)), (EVE_TYPE(0))), eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_ornot(EVE_VALUE(0), (EVE_TYPE(0))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(EVE_VALUE(0), (EVE_TYPE(1))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_ornot(EVE_VALUE(2), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(EVE_VALUE(1), (EVE_TYPE(0))), eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(0)), EVE_VALUE(0)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(0)), EVE_VALUE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(2)), EVE_VALUE(1)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot((EVE_TYPE(1)), EVE_VALUE(0)), eve::True<EVE_TYPE>() );
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    using i_t = eve::detail::as_integer_t<EVE_TYPE>; 
    TTS_EQUAL(eve::logical_ornot((i_t(0)), (EVE_TYPE(0))), eve::True<i_t>());
    TTS_EQUAL(eve::logical_ornot((i_t(0)), (EVE_TYPE(1))), eve::False<i_t>());
    TTS_EQUAL(eve::logical_ornot((i_t(2)), (EVE_TYPE(1))), eve::True<i_t>() );
    TTS_EQUAL(eve::logical_ornot((i_t(1)), (EVE_TYPE(0))), eve::True<i_t>());
    
    TTS_EQUAL(eve::logical_ornot((EVE_TYPE(0)), i_t(0)), eve::True<EVE_TYPE>());
    TTS_EQUAL(eve::logical_ornot((EVE_TYPE(0)), i_t(1)), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::logical_ornot((EVE_TYPE(2)), i_t(1)), eve::True<EVE_TYPE>() );
    TTS_EQUAL(eve::logical_ornot((EVE_TYPE(1)), i_t(0)), eve::True<EVE_TYPE>());
  }
}

TTS_CASE("Check eve::logical_ornot behavior on logicals")
{
  TTS_EQUAL(eve::logical_ornot(eve::False<EVE_TYPE>() , eve::False<EVE_TYPE>()) , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(eve::False<EVE_TYPE>() , eve::True<EVE_TYPE>() ) , eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_ornot(eve::True<EVE_TYPE>()  , eve::True<EVE_TYPE>() ) , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(eve::True<EVE_TYPE>()  , eve::False<EVE_TYPE>()) , eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_ornot(eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>()), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(eve::False<EVE_VALUE>(), eve::True<EVE_TYPE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_ornot(eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(eve::True<EVE_VALUE>() , eve::False<EVE_TYPE>()), eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_ornot(eve::False<EVE_TYPE>() , eve::False<EVE_VALUE>() ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(eve::False<EVE_TYPE>() , eve::True<EVE_VALUE>()  ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_ornot(eve::True<EVE_TYPE>()  , eve::True<EVE_VALUE>()  ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_ornot(eve::True<EVE_TYPE>()  , eve::False<EVE_VALUE>() ), eve::True<EVE_TYPE>() );
}
