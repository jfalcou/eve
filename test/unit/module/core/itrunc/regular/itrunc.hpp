//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/itrunc.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check itrunc return type")
{
  TTS_EXPR_IS(eve::itrunc(Type()), (eve::detail::as_integer_t<Type>));
}

TTS_CASE("Check eve::itrunc behavior")
{
  using i_t = eve::detail::as_integer_t<Type>; 
  TTS_EQUAL(eve::itrunc(Type(0)), i_t(0));
  TTS_EQUAL(eve::itrunc(Type(1)), i_t(1));
  TTS_EQUAL(eve::itrunc(Type(2)), i_t(2));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::itrunc(Type(-1)), i_t(-1));
    TTS_EQUAL(eve::itrunc(Type(-2)), i_t(-2));
  }

  if constexpr(std::is_floating_point_v<Value>)
  {
   TTS_EQUAL(eve::itrunc(Type(-1.3)), i_t(-1));
   TTS_EQUAL(eve::itrunc(Type(-1.5)), i_t(-1));
   TTS_EQUAL(eve::itrunc(Type(-1.6)), i_t(-1));
   TTS_EQUAL(eve::itrunc(Type(1.3)) , i_t(1));
   TTS_EQUAL(eve::itrunc(Type(1.5)) , i_t(1));
   TTS_EQUAL(eve::itrunc(Type(1.6)) , i_t(1));
  }
}
