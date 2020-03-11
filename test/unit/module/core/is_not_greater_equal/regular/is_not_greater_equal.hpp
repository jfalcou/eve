//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_not_greater_equal return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_not_greater_equal(EVE_TYPE() , EVE_TYPE() ), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::is_not_greater_equal(EVE_TYPE() , EVE_VALUE()), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::is_not_greater_equal(EVE_VALUE(), EVE_TYPE() ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::is_not_greater_equal behavior")
{
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_not_greater_equal(EVE_TYPE(1), eve::Nan<EVE_TYPE>()), eve::True<EVE_TYPE>());
    TTS_EQUAL(eve::is_not_greater_equal(eve::Nan<EVE_TYPE>(), EVE_TYPE(1)), eve::True<EVE_TYPE>());
  }

  TTS_EQUAL(eve::is_not_greater_equal(EVE_TYPE(1) , EVE_TYPE(1) ), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_TYPE(1) , EVE_VALUE(1)), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_VALUE(1), EVE_TYPE(1) ), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_TYPE(3) , EVE_TYPE(1) ), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_TYPE(3) , EVE_VALUE(1)), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_VALUE(3), EVE_TYPE(1) ), eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_TYPE(1) , EVE_TYPE(3) ), eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_TYPE(1) , EVE_VALUE(3)), eve::True<EVE_TYPE>()  );
  TTS_EQUAL(eve::is_not_greater_equal(EVE_VALUE(1), EVE_TYPE(3) ), eve::True<EVE_TYPE>()  );
}
