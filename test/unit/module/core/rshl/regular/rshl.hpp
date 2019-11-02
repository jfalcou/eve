//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rshl.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::rshl return type")
{
  using i_t = eve::detail::as_integer_t<Type, signed>;
  using u_t = eve::detail::as_integer_t<Type, unsigned>;

  TTS_EXPR_IS(eve::rshl(Type(), Type()) , (Type));
  TTS_EXPR_IS(eve::rshl(Type(), i_t())  , (Type));
  TTS_EXPR_IS(eve::rshl(Type(), u_t())  , (Type));
  TTS_EXPR_IS(eve::rshl(i_t() , Type())  , i_t);
  TTS_EXPR_IS(eve::rshl(u_t() , Type())  , u_t);
}

TTS_CASE("Check eve::rshl behavior")
{
  TTS_EQUAL(eve::rshl((Type(1)), (Type(4))  ), (Type(16)));

  TTS_EQUAL(eve::rshl((Type(1)),  4         ), (Type(16)));
  TTS_EQUAL(eve::rshl((Type(3)), -1         ), (Type( 1)));
  TTS_EQUAL(eve::rshl((Type(0)),  3         ), (Type( 0)));
  TTS_EQUAL(eve::rshl((Type(8)), -2         ), (Type( 2)));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::rshl(eve::Allbits<Type>(), 1), Type(-2));
    TTS_EQUAL(eve::rshl(eve::Allbits<Type>(), -1), eve::Allbits<Type>());
  }
  else
  {
    TTS_EQUAL(eve::rshl(eve::Allbits<Type>(), -1), eve::Allbits<Type>()/2 );
    TTS_EQUAL(eve::rshl(eve::Allbits<Type>(),  1), eve::Allbits<Type>() - 1 );
  }
}
