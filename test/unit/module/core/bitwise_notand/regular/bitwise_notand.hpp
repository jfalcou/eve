//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitwise_notand.hpp>
#include <eve/constant/allbits.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bitwise_notand return type")
{
  using eve::detail::as_integer_t;

  TTS_EXPR_IS(eve::bitwise_notand(Type(), Type())  , (Type));
  TTS_EXPR_IS(eve::bitwise_notand(Type(), Value()) , (Type));

  TTS_EXPR_IS(eve::bitwise_notand(Type(),(as_integer_t<Type, unsigned>())) , (Type));
  TTS_EXPR_IS(eve::bitwise_notand(Type(),(as_integer_t<Value, unsigned>())), (Type));
  TTS_EXPR_IS(eve::bitwise_notand(Type(),(as_integer_t<Type, signed>()))   , (Type));
  TTS_EXPR_IS(eve::bitwise_notand(Type(),(as_integer_t<Value, signed>()))  , (Type));

  TTS_EXPR_IS(eve::bitwise_notand((as_integer_t<Type, unsigned>()) , Type()), (as_integer_t<Type, unsigned>));
  TTS_EXPR_IS(eve::bitwise_notand((as_integer_t<Type, signed>())   , Type()), (as_integer_t<Type, signed>));
}

TTS_CASE( "Check eve::bitwise_notand behavior")
{
  using eve::detail::as_integer_t;
  using eve::bitwise_cast;
  using eve::as;

  TTS_EQUAL(eve::bitwise_notand((Type(0)), (Type(0)))  , (Type(0)));
  TTS_EQUAL(eve::bitwise_notand((Type(0)), (Value(0))) , (Type(0)));
  TTS_EQUAL(eve::bitwise_notand((Type(0)), (Type(1)))  , (Type(1)));
  TTS_EQUAL(eve::bitwise_notand((Type(0)), (Value(1))) , (Type(1)));
  TTS_EQUAL(eve::bitwise_notand((Type(1)), (Type(1)))  , (Type(0)));
  TTS_EQUAL(eve::bitwise_notand((Type(1)), (Value(1))) , (Type(0)));
  TTS_EQUAL(eve::bitwise_notand((Type(1)), (Type(0)))  , (Type(0)));
  TTS_EQUAL(eve::bitwise_notand((Type(1)), (Value(0))) , (Type(0)));

  using ui_t = as_integer_t<Type, unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;
  using si_t = as_integer_t<Type, signed>;
  using wi_t = as_integer_t<Value, signed>;

  TTS_EQUAL(eve::bitwise_notand((Type(0)), ui_t(1)), bitwise_cast(ui_t(1),as<Type>()));
  TTS_EQUAL(eve::bitwise_notand((Type(0)), vi_t(1)), bitwise_cast(ui_t(1),as<Type>()));
  TTS_EQUAL(eve::bitwise_notand((Type(0)), si_t(1)), bitwise_cast(si_t(1),as<Type>()));
  TTS_EQUAL(eve::bitwise_notand((Type(0)), wi_t(1)), bitwise_cast(si_t(1),as<Type>()));

  TTS_EQUAL(eve::bitwise_notand(ui_t(0), (Type(1))), bitwise_cast(Type(1),as<ui_t>()));
  TTS_EQUAL(eve::bitwise_notand(si_t(0), (Type(1))), bitwise_cast(Type(1),as<si_t>()));

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::bitwise_notand(Type(~3), Type(2) ) , Type(2));
    TTS_EQUAL(eve::bitwise_notand(Type(~3), Value(2)) , Type(2));
    TTS_EQUAL(eve::bitwise_notand(Type(~3), Type(1) ) , Type(1));
    TTS_EQUAL(eve::bitwise_notand(Type(~3), Value(1)) , Type(1));
  }
}
