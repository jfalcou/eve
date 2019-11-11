//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/shr.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE("Check eve::shr return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;

  TTS_EXPR_IS(eve::shr(Type(), Type()), (Type));
  TTS_EXPR_IS(eve::shr(Type(), i_t() ), (Type));
  TTS_EXPR_IS(eve::shr(Type(), u_t() ), (Type));
}

TTS_CASE("Check eve::shr behavior")
{
  TTS_EQUAL(eve::shr(Type( 0), 7), (Type(0)));
  TTS_EQUAL(eve::shr(Type(16), 4), (Type(1)));
  TTS_EQUAL(eve::shr(Type(12), 2), (Type(3)));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::shr(Type(-16), 4), (Type(-1)));
    TTS_EQUAL(eve::shr(Type(-12), 2), (Type(-3)));
    TTS_EQUAL(eve::shr(eve::Allbits<Type>(), 1), eve::Allbits<Type>());
  }
  else
  {
    TTS_EQUAL(eve::shr(eve::Allbits<Type>(), 1), eve::Allbits<Type>()/2 );
  }
}
