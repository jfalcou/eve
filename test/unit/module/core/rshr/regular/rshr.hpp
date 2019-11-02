//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rshr.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::rshr return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;

  TTS_EXPR_IS(eve::rshr(Type(), Type()) , (Type));
  TTS_EXPR_IS(eve::rshr(Type(), i_t())  , (Type));
  TTS_EXPR_IS(eve::rshr(Type(), u_t())  , (Type));
  TTS_EXPR_IS(eve::rshr(i_t() , Type())  , i_t);
  TTS_EXPR_IS(eve::rshr(u_t() , Type())  , u_t);
}

TTS_CASE("Check eve::rshr behavior")
{
  TTS_EQUAL(eve::rshr((Type(8)), (Type(2))  ), (Type(2)));

  TTS_EQUAL(eve::rshr((Type(1)), -4         ), (Type(16)));
  TTS_EQUAL(eve::rshr((Type(3)),  1         ), (Type( 1)));
  TTS_EQUAL(eve::rshr((Type(0)), -3         ), (Type( 0)));
  TTS_EQUAL(eve::rshr((Type(8)),  2         ), (Type( 2)));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::rshr(eve::Allbits<Type>(), -1), Type(-2));
    TTS_EQUAL(eve::rshr(eve::Allbits<Type>(),  1), eve::Allbits<Type>());
  }
  else
  {
    TTS_EQUAL(eve::rshr(eve::Allbits<Type>(),  1), eve::Allbits<Type>()/2 );
    TTS_EQUAL(eve::rshr(eve::Allbits<Type>(), -1), eve::Allbits<Type>() - 1 );
  }
}
