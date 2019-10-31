//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_imag.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::is_imag return type")
{
  TTS_EXPR_IS(eve::is_imag(Type(0)), (eve::logical<Type>));
}

TTS_CASE("Check eve::is_imag behavior")
{
  TTS_EQUAL(eve::is_imag(Type(0)), eve::True<Type>() );
  TTS_EQUAL(eve::is_imag(Type(2)), eve::False<Type>()  );
}
