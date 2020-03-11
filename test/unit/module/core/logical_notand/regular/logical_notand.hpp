//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_notand.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::logical_notand return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_notand(EVE_TYPE()         , EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(logical<EVE_TYPE>(), EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(logical<EVE_TYPE>(), logical<EVE_TYPE>())), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(EVE_TYPE()         , logical<EVE_TYPE>())), (logical<EVE_TYPE>));

  TTS_EXPR_IS((eve::logical_notand(EVE_VALUE()         , EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(EVE_TYPE()          , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(logical<EVE_TYPE>() , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(logical<EVE_VALUE>(), EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(logical<EVE_VALUE>(), logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(logical<EVE_TYPE>() , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(EVE_VALUE()         , logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_notand(EVE_TYPE()          , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::logical_notand behavior on scalars")
{
  TTS_EQUAL(eve::logical_notand((EVE_TYPE(0)), (EVE_TYPE(0))), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand((EVE_TYPE(0)), (EVE_TYPE(1))), eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_notand((EVE_TYPE(2)), (EVE_TYPE(1))), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand((EVE_TYPE(1)), (EVE_TYPE(0))), eve::False<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_notand(EVE_VALUE(0), (EVE_TYPE(0))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand(EVE_VALUE(0), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand(EVE_VALUE(2), (EVE_TYPE(1))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand(EVE_VALUE(1), (EVE_TYPE(0))), eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::logical_notand((EVE_TYPE(0)), EVE_VALUE(0)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand((EVE_TYPE(0)), EVE_VALUE(1)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand((EVE_TYPE(2)), EVE_VALUE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand((EVE_TYPE(1)), EVE_VALUE(0)), eve::False<EVE_TYPE>());
}

TTS_CASE("Check eve::logical_notand behavior on logicals")
{
  TTS_EQUAL(eve::logical_notand(eve::False<EVE_TYPE>() , eve::False<EVE_TYPE>()) , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand(eve::False<EVE_TYPE>() , eve::True<EVE_TYPE>() ) , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_notand(eve::True<EVE_TYPE>()  , eve::True<EVE_TYPE>() ) , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand(eve::True<EVE_TYPE>()  , eve::False<EVE_TYPE>()) , eve::False<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_notand(eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>()), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand(eve::False<EVE_VALUE>(), eve::True<EVE_TYPE>() ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand(eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand(eve::True<EVE_VALUE>() , eve::False<EVE_TYPE>()), eve::False<EVE_TYPE>());

  TTS_EQUAL(eve::logical_notand(eve::False<EVE_TYPE>() , eve::False<EVE_VALUE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand(eve::False<EVE_TYPE>() , eve::True<EVE_VALUE>()  ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_notand(eve::True<EVE_TYPE>()  , eve::True<EVE_VALUE>()  ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_notand(eve::True<EVE_TYPE>()  , eve::False<EVE_VALUE>() ), eve::False<EVE_TYPE>());
}
