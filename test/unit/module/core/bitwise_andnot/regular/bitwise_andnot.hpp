//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitwise_andnot.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bitwise_andnot return type")
{
  using eve::detail::as_integer_t;

  TTS_EXPR_IS(eve::bitwise_andnot(Type(), Type())  , (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(Type(), Value()) , (Type));

  TTS_EXPR_IS(eve::bitwise_andnot(Type(),(as_integer_t<Type, unsigned>())) , (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(Type(),(as_integer_t<Value, unsigned>())), (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(Type(),(as_integer_t<Type, signed>()))   , (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(Type(),(as_integer_t<Value, signed>()))  , (Type));

  TTS_EXPR_IS(eve::bitwise_andnot((as_integer_t<Type, unsigned>()) , Type()), (as_integer_t<Type, unsigned>));
  TTS_EXPR_IS(eve::bitwise_andnot((as_integer_t<Type, signed>())   , Type()), (as_integer_t<Type, signed>));
}

TTS_CASE( "Check bitwise_andnot behavior")
{
  using eve::detail::as_integer_t;

  TTS_EQUAL(eve::bitwise_andnot((Type(0)), (Type(0)))  , (Type(0)));
  TTS_EQUAL(eve::bitwise_andnot((Type(0)), (Value(0))) , (Type(0)));
  TTS_EQUAL(eve::bitwise_andnot((Type(0)), (Type(1)))  , (Type(0)));
  TTS_EQUAL(eve::bitwise_andnot((Type(0)), (Value(1))) , (Type(0)));
  TTS_EQUAL(eve::bitwise_andnot((Type(1)), (Type(1)))  , (Type(0)));
  TTS_EQUAL(eve::bitwise_andnot((Type(1)), (Value(1))) , (Type(0)));
  TTS_EQUAL(eve::bitwise_andnot((Type(1)), (Type(0)))  , (Type(1)));
  TTS_EQUAL(eve::bitwise_andnot((Type(1)), (Value(0))) , (Type(1)));

  using ui_t = as_integer_t<Type, unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;
  using si_t = as_integer_t<Type, signed>;
  using wi_t = as_integer_t<Value, signed>;

  TTS_EQUAL(eve::bitwise_andnot((Type(1)), ui_t(0)), (Type(1)));
  TTS_EQUAL(eve::bitwise_andnot((Type(1)), vi_t(0)), (Type(1)));
  TTS_EQUAL(eve::bitwise_andnot((Type(1)), si_t(0)), (Type(1)));
  TTS_EQUAL(eve::bitwise_andnot((Type(1)), wi_t(0)), (Type(1)));

  TTS_EQUAL(eve::bitwise_andnot(ui_t(1), (Type(0))), ui_t(1));
  TTS_EQUAL(eve::bitwise_andnot(si_t(1), (Type(0))), si_t(1));

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::bitwise_andnot(Type(3), Type(~2) ) , Type(2));
    TTS_EQUAL(eve::bitwise_andnot(Type(3), Value(~2)) , Type(2));
    TTS_EQUAL(eve::bitwise_andnot(Type(3), Type(~1) ) , Type(1));
    TTS_EQUAL(eve::bitwise_andnot(Type(3), Value(~1)) , Type(1));
  }
}
