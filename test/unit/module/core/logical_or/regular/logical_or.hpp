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

TTS_CASE("Check eve::logical_or return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_or(EVE_TYPE()         , EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(logical<EVE_TYPE>(), EVE_TYPE())         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(logical<EVE_TYPE>(), logical<EVE_TYPE>())), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(EVE_TYPE()         , logical<EVE_TYPE>())), (logical<EVE_TYPE>));

  TTS_EXPR_IS((eve::logical_or(EVE_VALUE()         , EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(EVE_TYPE()          , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(logical<EVE_TYPE>() , EVE_VALUE())          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(logical<EVE_VALUE>(), EVE_TYPE())           ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(logical<EVE_VALUE>(), logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(logical<EVE_TYPE>() , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(EVE_VALUE()         , logical<EVE_TYPE>())  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((eve::logical_or(EVE_TYPE()          , logical<EVE_VALUE>()) ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::operator|| return type")
{
  using eve::logical;

  TTS_EXPR_IS((logical<EVE_TYPE>()  || EVE_TYPE()         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((logical<EVE_TYPE>()  || logical<EVE_TYPE>()), (logical<EVE_TYPE>));
  TTS_EXPR_IS((EVE_TYPE()           || logical<EVE_TYPE>()), (logical<EVE_TYPE>));
  TTS_EXPR_IS((logical<EVE_TYPE>()  || EVE_VALUE()        ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((logical<EVE_VALUE>() || EVE_TYPE()         ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::logical_or behavior on scalars")
{
  TTS_EQUAL(eve::logical_or((EVE_TYPE(0)), (EVE_TYPE(0))), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or((EVE_TYPE(0)), (EVE_TYPE(1))), eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_or((EVE_TYPE(2)), (EVE_TYPE(1))), eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_or((EVE_TYPE(1)), (EVE_TYPE(0))), eve::True<EVE_TYPE>()  );

  TTS_EQUAL(eve::logical_or(EVE_VALUE(0), (EVE_TYPE(0))), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_or(EVE_VALUE(0), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or(EVE_VALUE(2), (EVE_TYPE(1))), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or(EVE_VALUE(1), (EVE_TYPE(0))), eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_or((EVE_TYPE(0)), EVE_VALUE(0)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_or((EVE_TYPE(0)), EVE_VALUE(1)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or((EVE_TYPE(2)), EVE_VALUE(1)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or((EVE_TYPE(1)), EVE_VALUE(0)), eve::True<EVE_TYPE>() );
}

TTS_CASE("Check eve::logical_or behavior on logicals")
{
  TTS_EQUAL(eve::logical_or(eve::False<EVE_TYPE>() , eve::False<EVE_TYPE>()) , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or(eve::False<EVE_TYPE>() , eve::True<EVE_TYPE>() ) , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_or(eve::True<EVE_TYPE>()  , eve::True<EVE_TYPE>() ) , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::logical_or(eve::True<EVE_TYPE>()  , eve::False<EVE_TYPE>()) , eve::True<EVE_TYPE>()  );

  TTS_EQUAL(eve::logical_or(eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>()), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_or(eve::False<EVE_VALUE>(), eve::True<EVE_TYPE>() ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or(eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or(eve::True<EVE_VALUE>() , eve::False<EVE_TYPE>()), eve::True<EVE_TYPE>() );

  TTS_EQUAL(eve::logical_or(eve::False<EVE_TYPE>() , eve::False<EVE_VALUE>() ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::logical_or(eve::False<EVE_TYPE>() , eve::True<EVE_VALUE>()  ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or(eve::True<EVE_TYPE>()  , eve::True<EVE_VALUE>()  ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::logical_or(eve::True<EVE_TYPE>()  , eve::False<EVE_VALUE>() ), eve::True<EVE_TYPE>() );
}

TTS_CASE("Check eve::operator|| behavior on logicals")
{
  TTS_EQUAL(eve::False<EVE_TYPE>()  || eve::False<EVE_TYPE>(), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::False<EVE_TYPE>()  || eve::True<EVE_TYPE>() , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::True<EVE_TYPE>()   || eve::True<EVE_TYPE>() , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::True<EVE_TYPE>()   || eve::False<EVE_TYPE>(), eve::True<EVE_TYPE>()  );

  TTS_EQUAL(eve::False<EVE_VALUE>() || eve::False<EVE_TYPE>(), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::False<EVE_VALUE>() || eve::True<EVE_TYPE>() , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::True<EVE_VALUE>()  || eve::True<EVE_TYPE>() , eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::True<EVE_VALUE>()  || eve::False<EVE_TYPE>(), eve::True<EVE_TYPE>()  );

  TTS_EQUAL(eve::False<EVE_TYPE>()  || eve::False<EVE_VALUE>(), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::False<EVE_TYPE>()  || eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::True<EVE_TYPE>()   || eve::True<EVE_VALUE>() , eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::True<EVE_TYPE>()   || eve::False<EVE_VALUE>(), eve::True<EVE_TYPE>() );
}
