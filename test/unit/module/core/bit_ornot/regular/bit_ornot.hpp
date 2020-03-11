//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_ornot.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_ornot return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS(eve::bit_ornot(EVE_TYPE(), EVE_TYPE()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_ornot(EVE_TYPE(), EVE_VALUE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_ornot(EVE_TYPE(), ui_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_ornot(EVE_TYPE(), vi_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_ornot(ui_t(), EVE_TYPE()) , ui_t  );
}

TTS_CASE( "Check eve::bit_ornot behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using ui_t = as_integer_t<EVE_TYPE , unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  constexpr auto u  = 0xAAAAAAAAAAAAAAAAULL;
  constexpr auto d  = 0x6666666666666666ULL;
  constexpr auto m  = 0x7777777777777777ULL;
  constexpr auto n  = 0xBBBBBBBBBBBBBBBBULL;

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  ui_t um( static_cast<vi_t>(m) );
  ui_t un( static_cast<vi_t>(n) );
  auto td = bit_cast(ud, as<EVE_TYPE>());
  auto tu = bit_cast(uu, as<EVE_TYPE>());
  auto tm = bit_cast(um, as<EVE_TYPE>());
  auto tn = bit_cast(un, as<EVE_TYPE>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<EVE_VALUE>());
  auto vd = bit_cast(sd, as<EVE_VALUE>());

  TTS_SUBCASE("wide<T> x wide<T> case")
  {
    TTS_EQUAL(eve::bit_ornot(tu,td),tn);
    TTS_EQUAL(eve::bit_ornot(td,tu),tm);
  }

  TTS_SUBCASE("wide<T> x T case")
  {
    TTS_EQUAL(eve::bit_ornot(tu,vd),tn);
    TTS_EQUAL(eve::bit_ornot(td,vu),tm);
  }

  TTS_SUBCASE("wide<T> x wide<U> case")
  {
    TTS_EQUAL(eve::bit_ornot(tu,ud),tn);
    TTS_EQUAL(eve::bit_ornot(td,uu),tm);
  }

  TTS_SUBCASE("wide<T> x U case")
  {
    TTS_EQUAL(eve::bit_ornot(tu,sd),tn);
    TTS_EQUAL(eve::bit_ornot(td,su),tm);
  }
}
