//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_less.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_less return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_less(EVE_TYPE() , EVE_TYPE()  ), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::is_less(EVE_TYPE() , EVE_VALUE() ), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::is_less(EVE_VALUE(), EVE_TYPE()  ), (logical<EVE_TYPE>));
}

#if defined(EVE_SIMD_TESTS)
TTS_CASE("Check eve::operator< return type")
{
  using eve::logical;

  TTS_EXPR_IS((EVE_TYPE()   < EVE_TYPE() ), (logical<EVE_TYPE>));
  TTS_EXPR_IS((EVE_TYPE()   < EVE_VALUE()), (logical<EVE_TYPE>));
  TTS_EXPR_IS((EVE_VALUE()  < EVE_TYPE() ), (logical<EVE_TYPE>));
}
#endif

TTS_CASE("Check eve::is_less behavior")
{
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::is_less(EVE_TYPE(1), eve::Nan<EVE_TYPE>()), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::is_less(eve::Nan<EVE_TYPE>(), EVE_TYPE(1)), eve::False<EVE_TYPE>());
  }

  TTS_EQUAL(eve::is_less(EVE_TYPE(1) , EVE_TYPE(1) ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_less(EVE_TYPE(1) , EVE_VALUE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_less(EVE_VALUE(1), EVE_TYPE(1) ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_less(EVE_TYPE(3) , EVE_TYPE(1) ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_less(EVE_TYPE(3) , EVE_VALUE(1)), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_less(EVE_VALUE(3), EVE_TYPE(1) ), eve::False<EVE_TYPE>());
  TTS_EQUAL(eve::is_less(EVE_TYPE(1) , EVE_TYPE(3) ), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::is_less(EVE_TYPE(1) , EVE_VALUE(3)), eve::True<EVE_TYPE>() );
  TTS_EQUAL(eve::is_less(EVE_VALUE(1), EVE_TYPE(3) ), eve::True<EVE_TYPE>() );
}

TTS_CASE("Check eve::operator< behavior")
{
  using eve::logical;

  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL((eve::Nan<EVE_TYPE>() < eve::Nan<EVE_TYPE>()) , eve::False<EVE_TYPE>());
    TTS_EQUAL((eve::Nan<EVE_TYPE>() < EVE_TYPE(4))          , eve::False<EVE_TYPE>());
  }

  TTS_EQUAL( (EVE_TYPE(1)   < EVE_TYPE(1) ) , eve::False<EVE_TYPE>());
  TTS_EQUAL( (EVE_VALUE(1)  < EVE_TYPE(1) ) , eve::False<EVE_TYPE>());
  TTS_EQUAL( (EVE_TYPE(1)   < EVE_VALUE(1)) , eve::False<EVE_TYPE>());
  TTS_EQUAL( (EVE_TYPE(3)   < EVE_TYPE(1) ) , eve::False<EVE_TYPE>());
  TTS_EQUAL( (EVE_VALUE(3)  < EVE_TYPE(1) ) , eve::False<EVE_TYPE>());
  TTS_EQUAL( (EVE_TYPE(3)   < EVE_VALUE(1)) , eve::False<EVE_TYPE>());
  TTS_EQUAL( (EVE_TYPE(1)   < EVE_TYPE(3) ) , eve::True<EVE_TYPE>() );
  TTS_EQUAL( (EVE_VALUE(1)  < EVE_TYPE(3) ) , eve::True<EVE_TYPE>() );
  TTS_EQUAL( (EVE_TYPE(1)   < EVE_VALUE(3)) , eve::True<EVE_TYPE>() );
}
