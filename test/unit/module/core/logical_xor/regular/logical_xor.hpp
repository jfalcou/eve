//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_xor.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::logical_xor return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_xor(EVE_TYPE()         , EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(logical<EVE_TYPE>(), EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(logical<EVE_TYPE>(), logical<EVE_TYPE>())), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(EVE_TYPE()         , logical<EVE_TYPE>())), (logical<EVE_TYPE>));

  TTS_EXPR_IS((eve::logical_xor(EVE_VALUE()         , EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(EVE_TYPE()          , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(logical<EVE_TYPE>() , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(logical<EVE_VALUE>(), EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(logical<EVE_VALUE>(), logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(logical<EVE_TYPE>() , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(EVE_VALUE()         , logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_xor(EVE_TYPE()          , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::logical_xor behavior on scalars")
{
  TTS_EQUAL(eve::logical_xor((EVE_TYPE(0)), (EVE_TYPE(0))), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor((EVE_TYPE(0)), (EVE_TYPE(1))), eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_xor((EVE_TYPE(2)), (EVE_TYPE(1))), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor((EVE_TYPE(1)), (EVE_TYPE(0))), eve::True<EVE_TYPE>()  );

  TTS_EQUAL(eve::logical_xor(EVE_VALUE(0), (EVE_TYPE(0))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor(EVE_VALUE(0), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor(EVE_VALUE(2), (EVE_TYPE(1))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor(EVE_VALUE(1), (EVE_TYPE(0))), eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_xor((EVE_TYPE(0)), EVE_VALUE(0)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor((EVE_TYPE(0)), EVE_VALUE(1)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor((EVE_TYPE(2)), EVE_VALUE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor((EVE_TYPE(1)), EVE_VALUE(0)), eve::True<EVE_TYPE>() );
}

TTS_CASE("Check eve::logical_xor behavior on logicals")
{
  TTS_EQUAL(eve::logical_xor(eve::False<EVE_TYPE>() , eve::False<EVE_TYPE>()) , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor(eve::False<EVE_TYPE>() , eve::True<EVE_TYPE>() ) , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_xor(eve::True<EVE_TYPE>()  , eve::True<EVE_TYPE>() ) , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor(eve::True<EVE_TYPE>()  , eve::False<EVE_TYPE>()) , eve::True<EVE_TYPE>()  );

  TTS_EQUAL(eve::logical_xor(eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>()), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor(eve::False<EVE_VALUE>(), eve::True<EVE_TYPE>() ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor(eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor(eve::True<EVE_VALUE>() , eve::False<EVE_TYPE>()), eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_xor(eve::False<EVE_TYPE>() , eve::False<EVE_VALUE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor(eve::False<EVE_TYPE>() , eve::True<EVE_VALUE>()  ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_xor(eve::True<EVE_TYPE>()  , eve::True<EVE_VALUE>()  ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_xor(eve::True<EVE_TYPE>()  , eve::False<EVE_VALUE>() ), eve::True<EVE_TYPE>() );
}
