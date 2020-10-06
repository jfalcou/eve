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
#include <eve/traits.hpp>
#include <eve/arch/abi_of.hpp>

TTS_CASE("Check eve::logical_or return type")
{
  TTS_EXPR_IS(eve::logical_or(EVE_TYPE()               , EVE_TYPE()               ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(eve::logical<EVE_TYPE>() , EVE_TYPE()               ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(eve::logical<EVE_TYPE>() , eve::logical<EVE_TYPE>() ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(EVE_TYPE()               , eve::logical<EVE_TYPE>() ), eve::logical<EVE_TYPE>);

  TTS_EXPR_IS(eve::logical_or(EVE_VALUE()               , EVE_TYPE()                ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(EVE_TYPE()                , EVE_VALUE()               ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(eve::logical<EVE_TYPE>()  , EVE_VALUE()               ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(eve::logical<EVE_VALUE>() , EVE_TYPE()                ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(eve::logical<EVE_VALUE>() , eve::logical<EVE_TYPE>()  ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(eve::logical<EVE_TYPE>()  , eve::logical<EVE_VALUE>() ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(EVE_VALUE()               , eve::logical<EVE_TYPE>()  ), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical_or(EVE_TYPE()                , eve::logical<EVE_VALUE>() ), eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::operator|| return type")
{
  TTS_EXPR_IS(eve::logical<EVE_TYPE>()   || EVE_TYPE()              , eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical<EVE_TYPE>()   || eve::logical<EVE_TYPE>(), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(EVE_TYPE()                 || eve::logical<EVE_TYPE>(), eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical<EVE_TYPE>()   || EVE_VALUE()            , eve::logical<EVE_TYPE>);
  TTS_EXPR_IS(eve::logical<EVE_VALUE>() || EVE_TYPE()              , eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::logical_or behavior on scalars")
{
  TTS_EQUAL(eve::logical_or(EVE_TYPE(0), EVE_TYPE(0)), eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(EVE_TYPE(0), EVE_TYPE(1)), eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL(eve::logical_or(EVE_TYPE(2), EVE_TYPE(1)), eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL(eve::logical_or(EVE_TYPE(1), EVE_TYPE(0)), eve::true_(eve::as<EVE_TYPE>())  );

  TTS_EQUAL(eve::logical_or(EVE_VALUE(0), EVE_TYPE(0)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_or(EVE_VALUE(0), EVE_TYPE(1)), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(EVE_VALUE(2), EVE_TYPE(1)), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(EVE_VALUE(1), EVE_TYPE(0)), eve::true_(eve::as<EVE_TYPE>()) );

  TTS_EQUAL(eve::logical_or(EVE_TYPE(0), EVE_VALUE(0)), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_or(EVE_TYPE(0), EVE_VALUE(1)), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(EVE_TYPE(2), EVE_VALUE(1)), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(EVE_TYPE(1), EVE_VALUE(0)), eve::true_(eve::as<EVE_TYPE>()) );

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    using i_t = eve::detail::as_integer_t<EVE_TYPE>;
    TTS_EQUAL(eve::logical_or(i_t(0), EVE_TYPE(0)), eve::false_(eve::as<i_t>()));
    TTS_EQUAL(eve::logical_or(i_t(0), EVE_TYPE(1)), eve::true_(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_or(i_t(2), EVE_TYPE(1)), eve::true_(eve::as<i_t>()) );
    TTS_EQUAL(eve::logical_or(i_t(1), EVE_TYPE(0)), eve::true_(eve::as<i_t>()) );

    TTS_EQUAL(eve::logical_or(EVE_TYPE(0), i_t(0)), eve::false_(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::logical_or(EVE_TYPE(0), i_t(1)), eve::true_(eve::as<EVE_TYPE>()) );
    TTS_EQUAL(eve::logical_or(EVE_TYPE(2), i_t(1)), eve::true_(eve::as<EVE_TYPE>()) );
    TTS_EQUAL(eve::logical_or(EVE_TYPE(1), i_t(0)), eve::true_(eve::as<EVE_TYPE>()) );
  }
}

TTS_CASE("Check eve::logical_or behavior on logicals")
{
  TTS_EQUAL(eve::logical_or(eve::false_(eve::as<EVE_TYPE>()) , eve::false_(eve::as<EVE_TYPE>())) , eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(eve::false_(eve::as<EVE_TYPE>()) , eve::true_(eve::as<EVE_TYPE>()) ) , eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL(eve::logical_or(eve::true_(eve::as<EVE_TYPE>())  , eve::true_(eve::as<EVE_TYPE>()) ) , eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL(eve::logical_or(eve::true_(eve::as<EVE_TYPE>())  , eve::false_(eve::as<EVE_TYPE>())) , eve::true_(eve::as<EVE_TYPE>())  );

  TTS_EQUAL(eve::logical_or(eve::false_(eve::as<EVE_VALUE>()), eve::false_(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_or(eve::false_(eve::as<EVE_VALUE>()), eve::true_(eve::as<EVE_TYPE>()) ), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(eve::true_(eve::as<EVE_VALUE>()) , eve::true_(eve::as<EVE_TYPE>()) ), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(eve::true_(eve::as<EVE_VALUE>()) , eve::false_(eve::as<EVE_TYPE>())), eve::true_(eve::as<EVE_TYPE>()) );

  TTS_EQUAL(eve::logical_or(eve::false_(eve::as<EVE_TYPE>()) , eve::false_(eve::as<EVE_VALUE>()) ), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::logical_or(eve::false_(eve::as<EVE_TYPE>()) , eve::true_(eve::as<EVE_VALUE>())  ), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(eve::true_(eve::as<EVE_TYPE>())  , eve::true_(eve::as<EVE_VALUE>())  ), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::logical_or(eve::true_(eve::as<EVE_TYPE>())  , eve::false_(eve::as<EVE_VALUE>()) ), eve::true_(eve::as<EVE_TYPE>()) );
}

TTS_CASE("Check eve::operator|| behavior on logicals")
{
  TTS_EQUAL((eve::false_(eve::as<EVE_TYPE>())  || eve::false_(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL((eve::false_(eve::as<EVE_TYPE>())  || eve::true_(eve::as<EVE_TYPE>()) ), eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL((eve::true_(eve::as<EVE_TYPE>())   || eve::true_(eve::as<EVE_TYPE>()) ), eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL((eve::true_(eve::as<EVE_TYPE>())   || eve::false_(eve::as<EVE_TYPE>())), eve::true_(eve::as<EVE_TYPE>())  );

  TTS_EQUAL((eve::false_(eve::as<EVE_VALUE>()) || eve::false_(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL((eve::false_(eve::as<EVE_VALUE>()) || eve::true_(eve::as<EVE_TYPE>()) ), eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL((eve::true_(eve::as<EVE_VALUE>())  || eve::true_(eve::as<EVE_TYPE>()) ), eve::true_(eve::as<EVE_TYPE>())  );
  TTS_EQUAL((eve::true_(eve::as<EVE_VALUE>())  || eve::false_(eve::as<EVE_TYPE>())), eve::true_(eve::as<EVE_TYPE>())  );

  TTS_EQUAL((eve::false_(eve::as<EVE_TYPE>())  || eve::false_(eve::as<EVE_VALUE>())), eve::false_(eve::as<EVE_TYPE>()));
  TTS_EQUAL((eve::false_(eve::as<EVE_TYPE>())  || eve::true_(eve::as<EVE_VALUE>()) ), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL((eve::true_(eve::as<EVE_TYPE>())   || eve::true_(eve::as<EVE_VALUE>()) ), eve::true_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL((eve::true_(eve::as<EVE_TYPE>())   || eve::false_(eve::as<EVE_VALUE>())), eve::true_(eve::as<EVE_TYPE>()) );
}
