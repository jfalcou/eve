//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_andnot.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE("Check eve::logical_andnot return type")
{

  TTS_EXPR_IS(eve::logical_andnot(EVE_TYPE()              , EVE_TYPE()              ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_andnot(eve::logical<EVE_TYPE>(), EVE_TYPE()              ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_andnot(eve::logical<EVE_TYPE>(), eve::logical<EVE_TYPE>()), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_andnot(EVE_TYPE()              , eve::logical<EVE_TYPE>()), eve::logical<EVE_TYPE>);

  TTS_EXPR_IS(eve::logical_andnot(EVE_VALUE()               , EVE_TYPE()                 ) , eve::logical<EVE_TYPE> );
  TTS_EXPR_IS(eve::logical_andnot(EVE_TYPE()                 , EVE_VALUE()               ) , eve::logical<EVE_TYPE> );
  TTS_EXPR_IS(eve::logical_andnot(eve::logical<EVE_TYPE>()   , EVE_VALUE()               ) , eve::logical<EVE_TYPE> );
  TTS_EXPR_IS(eve::logical_andnot(eve::logical<EVE_VALUE>() , EVE_TYPE()                 ) , eve::logical<EVE_TYPE> );
  TTS_EXPR_IS(eve::logical_andnot(eve::logical<EVE_VALUE>() , eve::logical<EVE_TYPE>()   ) , eve::logical<EVE_TYPE> );
  TTS_EXPR_IS(eve::logical_andnot(eve::logical<EVE_TYPE>()   , eve::logical<EVE_VALUE>() ) , eve::logical<EVE_TYPE> );
  TTS_EXPR_IS(eve::logical_andnot(EVE_VALUE()               , eve::logical<EVE_TYPE>()   ) , eve::logical<EVE_TYPE> );
  TTS_EXPR_IS(eve::logical_andnot(EVE_TYPE()                 , eve::logical<EVE_VALUE>() ) , eve::logical<EVE_TYPE> );
}

TTS_CASE("Check eve::logical_andnot behavior on scalars")
{

  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(0), EVE_TYPE(0)), eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(0), EVE_TYPE(1)), eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(2), EVE_TYPE(1)), eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(1), EVE_TYPE(0)), eve::true_(eve::as<EVE_TYPE>())  );

  TTS_EQUAL(eve::logical_andnot(EVE_VALUE(0), EVE_TYPE(0)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(EVE_VALUE(0), EVE_TYPE(1)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(EVE_VALUE(2), EVE_TYPE(1)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(EVE_VALUE(1), EVE_TYPE(0)), eve::true_(eve::as<EVE_TYPE>()) );

  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(0), EVE_VALUE(0)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(0), EVE_VALUE(1)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(2), EVE_VALUE(1)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(EVE_TYPE(1), EVE_VALUE(0)), eve::true_(eve::as<EVE_TYPE>()) );

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    using i_t = eve::detail::as_integer_t<EVE_TYPE>;
    TTS_EQUAL(eve::logical_andnot(i_t(0), EVE_TYPE(0)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_andnot(i_t(0), EVE_TYPE(1)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_andnot(i_t(2), EVE_TYPE(1)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_andnot(i_t(1), EVE_TYPE(0)), eve::true_(eve::as<i_t>()) );

    TTS_EQUAL(eve::logical_andnot(EVE_TYPE(0), i_t(0)), eve::false_(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::logical_andnot(EVE_TYPE(0), i_t(1)), eve::false_(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::logical_andnot(EVE_TYPE(2), i_t(1)), eve::false_(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::logical_andnot(EVE_TYPE(1), i_t(0)), eve::true_(eve::as<EVE_TYPE>()) );
  }
}

TTS_CASE("Check eve::logical_andnot behavior on logicals")
{

  TTS_EQUAL(eve::logical_andnot(eve::false_(eve::as<EVE_TYPE>()) , eve::false_(eve::as<EVE_TYPE>())) , eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_andnot(eve::false_(eve::as<EVE_TYPE>()) , eve::true_(eve::as<EVE_TYPE>()) ) , eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_andnot(eve::true_(eve::as<EVE_TYPE>())  , eve::true_(eve::as<EVE_TYPE>()) ) , eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_andnot(eve::true_(eve::as<EVE_TYPE>())  , eve::false_(eve::as<EVE_TYPE>())) , eve::true_(eve::as<EVE_TYPE>())  );

  TTS_EQUAL(eve::logical_andnot(eve::false_(eve::as<EVE_VALUE>()), eve::false_(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(eve::false_(eve::as<EVE_VALUE>()), eve::true_(eve::as<EVE_TYPE>()) ), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(eve::true_(eve::as<EVE_VALUE>()) , eve::true_(eve::as<EVE_TYPE>()) ), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(eve::true_(eve::as<EVE_VALUE>()) , eve::false_(eve::as<EVE_TYPE>())), eve::true_(eve::as<EVE_TYPE>()) );

  TTS_EQUAL(eve::logical_andnot(eve::false_(eve::as<EVE_TYPE>()) , eve::false_(eve::as<EVE_VALUE>()) ), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(eve::false_(eve::as<EVE_TYPE>()) , eve::true_(eve::as<EVE_VALUE>())  ), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(eve::true_(eve::as<EVE_TYPE>())  , eve::true_(eve::as<EVE_VALUE>())  ), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_andnot(eve::true_(eve::as<EVE_TYPE>())  , eve::false_(eve::as<EVE_VALUE>()) ), eve::true_(eve::as<EVE_TYPE>()) );
}
