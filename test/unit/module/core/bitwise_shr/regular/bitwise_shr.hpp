//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitwise_shr.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bitwise_shr return type")
{
  using ui_t = eve::detail::as_integer_t<Type, unsigned>;
  using si_t = eve::detail::as_integer_t<Type, signed>;

  TTS_EXPR_IS(eve::bitwise_shr(Type(), int()),  (Type));
  TTS_EXPR_IS(eve::bitwise_shr(Type(), ui_t()), (Type));
  TTS_EXPR_IS(eve::bitwise_shr(Type(), si_t()), (Type));
}

TTS_CASE( "Check eve::bitwise_shr behavior")
{
  TTS_EQUAL(eve::bitwise_shr((Type(4)), 1), (Type(2)) );
  TTS_EQUAL(eve::bitwise_shr((Type(2)), 1), (Type(1)) );
  TTS_EQUAL(eve::bitwise_shr((Type(1)), 1), (Type(0)) );
  TTS_EQUAL(eve::bitwise_shr((Type(0)), 1), (Type(0)) );

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::bitwise_shr((Type(-1)),(sizeof(Value)*8-1)), (Type(1)));
    TTS_EQUAL(eve::bitwise_shr((Type(-1)),(sizeof(Value)*8-2)), (Type(3)));
  }
  else
  {
    TTS_EQUAL(eve::bitwise_shr(eve::Valmax<Type>(),(sizeof(Value)*8-1)), (Type(1)));
    TTS_EQUAL(eve::bitwise_shr(eve::Valmax<Type>(),(sizeof(Value)*8-2)), (Type(3)));
  }
}
