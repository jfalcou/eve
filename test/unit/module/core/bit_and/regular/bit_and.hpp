//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_and.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_and return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<Type, unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;

  TTS_EXPR_IS(eve::bit_and(Type(), Type())  , (Type));
  TTS_EXPR_IS(eve::bit_and(Type(), Value()) , (Type));
  TTS_EXPR_IS(eve::bit_and(Type(), ui_t())  , (Type));
  TTS_EXPR_IS(eve::bit_and(Type(), vi_t())  , (Type));
  TTS_EXPR_IS(eve::bit_and(ui_t(), Type())  , ui_t  );
}

TTS_CASE( "Check eve::bit_and behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using ui_t = as_integer_t<Type , unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;
  constexpr auto d  = 0xAAAAAAAAAAAAAAAAULL;

  auto tz = Type(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bit_cast(ud, as<Type>());
  auto tu = bit_cast(uu, as<Type>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<Value>());
  auto vd = bit_cast(sd, as<Value>());

  TTS_SUBCASE("wide<T> x wide<T> case")
  {
    TTS_EQUAL(eve::bit_and(tu,tu),tu);
    TTS_EQUAL(eve::bit_and(tu,td),tz);
    TTS_EQUAL(eve::bit_and(td,tu),tz);
    TTS_EQUAL(eve::bit_and(td,td),td);
  }

  TTS_SUBCASE("wide<T> x T case")
  {
    TTS_EQUAL(eve::bit_and(tu,vu),tu);
    TTS_EQUAL(eve::bit_and(tu,vd),tz);
    TTS_EQUAL(eve::bit_and(td,vu),tz);
    TTS_EQUAL(eve::bit_and(td,vd),td);
  }

  TTS_SUBCASE("wide<T> x wide<U> case")
  {
    TTS_EQUAL(eve::bit_and(tu,uu),tu);
    TTS_EQUAL(eve::bit_and(tu,ud),tz);
    TTS_EQUAL(eve::bit_and(td,uu),tz);
    TTS_EQUAL(eve::bit_and(td,ud),td);
  }

  TTS_SUBCASE("wide<T> x U case")
  {
    TTS_EQUAL(eve::bit_and(tu,su),tu);
    TTS_EQUAL(eve::bit_and(tu,sd),tz);
    TTS_EQUAL(eve::bit_and(td,su),tz);
    TTS_EQUAL(eve::bit_and(td,sd),td);
  }
}
