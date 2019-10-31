//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_negative.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_negative return type")
{
  TTS_EXPR_IS(eve::is_negative(Type(0)), (eve::logical<Type>));
}

TTS_CASE("Check eve::is_negative behavior")
{
  TTS_EQUAL(eve::is_negative(Type(0)), eve::False<Type>());
  TTS_EQUAL(eve::is_negative(Type(2)), eve::False<Type>());

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::is_negative(Type(-1)), eve::True<Type>());
  }
  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::is_negative(eve::Zero<Type>()) , eve::False<Type>());
    TTS_EQUAL(eve::is_negative(eve::Mzero<Type>()), eve::True<Type>());

    if constexpr(eve::platform::supports_nans)
    {
      TTS_EQUAL(eve::is_negative( eve::Nan<Type>()), eve::True<Type>());
      TTS_EQUAL(eve::is_negative(-eve::Nan<Type>()), eve::False<Type>());
    }
  }
}
