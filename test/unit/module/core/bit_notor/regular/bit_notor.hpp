//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notor.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_notor return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<Type, unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;

  TTS_EXPR_IS(eve::bit_notor(Type(), Type()) , (Type));
  TTS_EXPR_IS(eve::bit_notor(Type(), Value()), (Type));
  TTS_EXPR_IS(eve::bit_notor(Type(), ui_t()) , (Type));
  TTS_EXPR_IS(eve::bit_notor(Type(), vi_t()) , (Type));
  TTS_EXPR_IS(eve::bit_notor(ui_t(), Type()) , ui_t  );
}

TTS_CASE( "Check eve::bit_notor behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using ui_t = as_integer_t<Type , unsigned>;
  using vi_t = as_integer_t<Value, unsigned>;

  constexpr auto u  = 0xAAAAAAAAAAAAAAAAULL;
  constexpr auto d  = 0x6666666666666666ULL;
  constexpr auto m  = 0x7777777777777777ULL;
  constexpr auto n  = 0xBBBBBBBBBBBBBBBBULL;

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  ui_t um( static_cast<vi_t>(m) );
  ui_t un( static_cast<vi_t>(n) );
  auto td = bit_cast(ud, as<Type>());
  auto tu = bit_cast(uu, as<Type>());
  auto tm = bit_cast(um, as<Type>());
  auto tn = bit_cast(un, as<Type>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<Value>());
  auto vd = bit_cast(sd, as<Value>());

  TTS_SUBCASE("wide<T> x wide<T> case")
  {
    TTS_EQUAL(eve::bit_notor(tu,td),tm);
    TTS_EQUAL(eve::bit_notor(td,tu),tn);
  }

  TTS_SUBCASE("wide<T> x T case")
  {
    TTS_EQUAL(eve::bit_notor(tu,vd),tm);
    TTS_EQUAL(eve::bit_notor(td,vu),tn);
  }

  TTS_SUBCASE("wide<T> x wide<U> case")
  {
    TTS_EQUAL(eve::bit_notor(tu,ud),tm);
    TTS_EQUAL(eve::bit_notor(td,uu),tn);
  }

  TTS_SUBCASE("wide<T> x U case")
  {
    TTS_EQUAL(eve::bit_notor(tu,sd),tm);
    TTS_EQUAL(eve::bit_notor(td,su),tn);
  }
}
