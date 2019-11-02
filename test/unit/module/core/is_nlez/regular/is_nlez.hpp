//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_nlez.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_nlez return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_nlez(Type() ), (logical<Type>));
}

TTS_CASE("Check eve::is_nlez behavior")
{
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::is_nlez(Type(-1)), eve::False<Type>());
  }

  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_nlez(eve::Nan<Type>()), eve::True<Type>());
  }

  TTS_EQUAL(eve::is_nlez(Type(0)), eve::False<Type>());
  TTS_EQUAL(eve::is_nlez(Type(3)), eve::True<Type>());
}
