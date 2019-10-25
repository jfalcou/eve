//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/shl.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE("Check eve::shl return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;

  TTS_EXPR_IS(eve::shl(Type(), Type()), (Type));
  TTS_EXPR_IS(eve::shl(Type(), i_t() ), (Type));
  TTS_EXPR_IS(eve::shl(Type(), u_t() ), (Type));
}

TTS_CASE("Check eve::shl behavior")
{
  TTS_EQUAL(eve::shl(Type(0), 7), (Type( 0)));
  TTS_EQUAL(eve::shl(Type(1), 4), (Type(16)));
  TTS_EQUAL(eve::shl(Type(3), 2), (Type(12)));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::shl(Type(-1), 4), (Type(-16)));
    TTS_EQUAL(eve::shl(Type(-3), 2), (Type(-12)));
    TTS_EQUAL(eve::shl(eve::Allbits<Type>(), 1), Type(-2));
  }
  else
  {
    TTS_EQUAL(eve::shl(eve::Allbits<Type>(), 1), eve::Allbits<Type>() - 1 );
  }
}
