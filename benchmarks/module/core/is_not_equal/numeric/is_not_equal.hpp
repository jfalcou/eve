//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_equal.hpp>
#include <eve/function/numeric.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::numeric_(eve::is_not_equal) return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(EVE_TYPE()          , EVE_TYPE()          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(EVE_TYPE()          , EVE_VALUE()         ), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(EVE_VALUE()         , EVE_TYPE()          ), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(logical<EVE_TYPE>() , logical<EVE_TYPE>() ), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(logical<EVE_TYPE>() , logical<EVE_VALUE>()), (logical<EVE_TYPE>));
  TTS_EXPR_IS(eve::numeric_(eve::is_not_equal)(logical<EVE_VALUE>(), logical<EVE_TYPE>() ), (logical<EVE_TYPE>));
}

TTS_CASE("Check eve::numeric_(eve::is_not_equal) behavior")
{
  using eve::logical;

  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>()), eve::False<EVE_TYPE>());
    TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::Nan<EVE_TYPE>(), EVE_TYPE(4))         , eve::True<EVE_TYPE>());
  }

  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(EVE_TYPE(1)           , EVE_TYPE(1) )           , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(EVE_TYPE(1)           , EVE_VALUE(1))           , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(EVE_TYPE(3)           , EVE_TYPE(1) )           , eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(EVE_TYPE(3)           , EVE_VALUE(1))           , eve::True<EVE_TYPE>());
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::True<EVE_TYPE>() , eve::True<EVE_TYPE>())  , eve::False<EVE_TYPE>() );
  TTS_EQUAL(eve::numeric_(eve::is_not_equal)(eve::True<EVE_TYPE>() , eve::False<EVE_TYPE>()) , eve::True<EVE_TYPE>());
}
