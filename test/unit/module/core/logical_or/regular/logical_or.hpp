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

// template<typename T> concept emulated1   = detail::is_emulated_v<abi_of_t<T, cardinal_t<T>>>;
//  template<typename T> concept aggregated1 = detail::is_aggregated_v<abi_of_t<T, cardinal_t<T>>>;
//  template<typename T> concept native1     = detail::is_native_v<abi_of_t<T, cardinal_t<T>>>;

TTS_CASE("Check eve::logical_or return type")
{
  using eve::logical;
  std::cout << tts::type_id<EVE_TYPE>() <<  " --- " << eve::native < EVE_TYPE> << std::endl;

  std::cout << tts::type_id<EVE_TYPE>() <<  " --- " << eve::native1 < EVE_TYPE> << std::endl;

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

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    using i_t = eve::detail::as_integer_t<EVE_TYPE>;
    TTS_EQUAL(eve::logical_or((i_t(0)), (EVE_TYPE(0))), eve::False<i_t>());
    TTS_EQUAL(eve::logical_or((i_t(0)), (EVE_TYPE(1))), eve::True<i_t>());
    TTS_EQUAL(eve::logical_or((i_t(2)), (EVE_TYPE(1))), eve::True<i_t>() );
    TTS_EQUAL(eve::logical_or((i_t(1)), (EVE_TYPE(0))), eve::True<i_t>());

    TTS_EQUAL(eve::logical_or((EVE_TYPE(0)), i_t(0)), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::logical_or((EVE_TYPE(0)), i_t(1)), eve::True<EVE_TYPE>());
    TTS_EQUAL(eve::logical_or((EVE_TYPE(2)), i_t(1)), eve::True<EVE_TYPE>() );
    TTS_EQUAL(eve::logical_or((EVE_TYPE(1)), i_t(0)), eve::True<EVE_TYPE>());
  }
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
