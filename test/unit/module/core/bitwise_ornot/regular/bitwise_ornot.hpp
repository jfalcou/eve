//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bitwise_ornot.hpp>
#include <eve/constant/allbits.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bitwise_ornot return type")
{
  using eve::detail::as_integer_t;

  TTS_EXPR_IS(eve::bitwise_ornot(Type(), Type())  , (Type));
  TTS_EXPR_IS(eve::bitwise_ornot(Type(), Value()) , (Type));

  TTS_EXPR_IS(eve::bitwise_ornot(Type(),(as_integer_t<Type, unsigned>())) , (Type));
  TTS_EXPR_IS(eve::bitwise_ornot(Type(),(as_integer_t<Value, unsigned>())), (Type));
  TTS_EXPR_IS(eve::bitwise_ornot(Type(),(as_integer_t<Type, signed>()))   , (Type));
  TTS_EXPR_IS(eve::bitwise_ornot(Type(),(as_integer_t<Value, signed>()))  , (Type));

  TTS_EXPR_IS(eve::bitwise_ornot((as_integer_t<Type, unsigned>()) , Type()), (as_integer_t<Type, unsigned>));
  TTS_EXPR_IS(eve::bitwise_ornot((as_integer_t<Type, signed>())   , Type()), (as_integer_t<Type, signed>));
}

TTS_CASE( "Check bitwise_ornot behavior")
{
  using eve::detail::as_integer_t;
  using eve::bitwise_cast;
  using eve::as;

  using ui_t = as_integer_t<Type, unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;
  using si_t = as_integer_t<Type, signed>;
  using wi_t = as_integer_t<Value, signed>;

  auto vz = Type(0);
  auto sz = Value(0);
  auto vo = eve::Allbits<Type>();
  auto so = eve::Allbits<Value>();

  TTS_IEEE_EQUAL(eve::bitwise_ornot(vz, vz), vo );
  TTS_IEEE_EQUAL(eve::bitwise_ornot(vz, sz), vo );
  TTS_EQUAL     (eve::bitwise_ornot(vz, vo), vz );
  TTS_EQUAL     (eve::bitwise_ornot(vz, so), vz );
  TTS_IEEE_EQUAL(eve::bitwise_ornot(vo, vz), vo );
  TTS_IEEE_EQUAL(eve::bitwise_ornot(vo, sz), vo );
  TTS_IEEE_EQUAL(eve::bitwise_ornot(vo, vo), vo );
  TTS_IEEE_EQUAL(eve::bitwise_ornot(vo, so), vo );

  TTS_EQUAL(eve::bitwise_ornot((Type(0)), ui_t(~1)), bitwise_cast(ui_t(1),as<Type>()));
  TTS_EQUAL(eve::bitwise_ornot((Type(0)), vi_t(~1)), bitwise_cast(ui_t(1),as<Type>()));
  TTS_EQUAL(eve::bitwise_ornot((Type(0)), si_t(~1)), bitwise_cast(si_t(1),as<Type>()));
  TTS_EQUAL(eve::bitwise_ornot((Type(0)), wi_t(~1)), bitwise_cast(si_t(1),as<Type>()));

  TTS_EQUAL(eve::bitwise_ornot(ui_t(0), (Type(0))), eve::Allbits<ui_t>());
  TTS_EQUAL(eve::bitwise_ornot(si_t(0), (Type(0))), eve::Allbits<si_t>());

  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL(eve::bitwise_ornot(Type(2), Type(~1) ) , Type(3));
    TTS_EQUAL(eve::bitwise_ornot(Type(2), Value(~1)) , Type(3));
    TTS_EQUAL(eve::bitwise_ornot(Type(2), Type(~1) ) , Type(3));
    TTS_EQUAL(eve::bitwise_ornot(Type(2), Value(~1)) , Type(3));
  }
}
