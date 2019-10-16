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
  using ui_t = as_integer_t<Type, unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;

  TTS_EXPR_IS(eve::bitwise_andnot(Type(), Type()) , (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(Type(), Value()), (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(Type(), ui_t()) , (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(Type(), vi_t()) , (Type));
  TTS_EXPR_IS(eve::bitwise_andnot(ui_t(), Type()) , ui_t  );
}

TTS_CASE( "Check eve::bitwise_andnot behavior")
{
  using eve::detail::as_integer_t;
  using eve::bitwise_cast;
  using eve::as;

  using ui_t = as_integer_t<Type , unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;
  constexpr auto d  = 0xAAAAAAAAAAAAAAAAULL;

  auto tz = Type(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bitwise_cast(ud, as<Type>());
  auto tu = bitwise_cast(uu, as<Type>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bitwise_cast(su, as<Value>());
  auto vd = bitwise_cast(sd, as<Value>());

  TTS_SUBCASE("wide<T> x wide<T> case")
  {
    TTS_EQUAL(eve::bitwise_andnot(tu,tu),tz);
    TTS_EQUAL(eve::bitwise_andnot(tu,td),tu);
    TTS_EQUAL(eve::bitwise_andnot(td,tu),td);
    TTS_EQUAL(eve::bitwise_andnot(td,td),tz);
  }

  TTS_SUBCASE("wide<T> x T case")
  {
    TTS_EQUAL(eve::bitwise_andnot(tu,vu),tz);
    TTS_EQUAL(eve::bitwise_andnot(tu,vd),tu);
    TTS_EQUAL(eve::bitwise_andnot(td,vu),td);
    TTS_EQUAL(eve::bitwise_andnot(td,vd),tz);
  }

  TTS_SUBCASE("wide<T> x wide<U> case")
  {
    TTS_EQUAL(eve::bitwise_andnot(tu,uu),tz);
    TTS_EQUAL(eve::bitwise_andnot(tu,ud),tu);
    TTS_EQUAL(eve::bitwise_andnot(td,uu),td);
    TTS_EQUAL(eve::bitwise_andnot(td,ud),tz);
  }

  TTS_SUBCASE("wide<T> x U case")
  {
    TTS_EQUAL(eve::bitwise_andnot(tu,su),tz);
    TTS_EQUAL(eve::bitwise_andnot(tu,sd),tu);
    TTS_EQUAL(eve::bitwise_andnot(td,su),td);
    TTS_EQUAL(eve::bitwise_andnot(td,sd),tz);
  }
}
