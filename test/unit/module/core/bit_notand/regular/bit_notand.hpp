//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notand.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_notand return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS(eve::bit_notand(EVE_TYPE(), EVE_TYPE()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_notand(EVE_TYPE(), EVE_VALUE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_notand(EVE_TYPE(), ui_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_notand(EVE_TYPE(), vi_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_notand(ui_t(), EVE_TYPE()) , ui_t  );
}

TTS_CASE( "Check eve::bit_notand behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using ui_t = as_integer_t<EVE_TYPE , unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;
  constexpr auto d  = 0xAAAAAAAAAAAAAAAAULL;

  auto tz = EVE_TYPE(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bit_cast(ud, as<EVE_TYPE>());
  auto tu = bit_cast(uu, as<EVE_TYPE>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<EVE_VALUE>());
  auto vd = bit_cast(sd, as<EVE_VALUE>());

  TTS_SUBCASE("wide<T> x wide<T> case")
  {
    TTS_EQUAL(eve::bit_notand(tu,tu),tz);
    TTS_EQUAL(eve::bit_notand(tu,td),td);
    TTS_EQUAL(eve::bit_notand(td,tu),tu);
    TTS_EQUAL(eve::bit_notand(td,td),tz);
  }

  TTS_SUBCASE("wide<T> x T case")
  {
    TTS_EQUAL(eve::bit_notand(tu,vu),tz);
    TTS_EQUAL(eve::bit_notand(tu,vd),td);
    TTS_EQUAL(eve::bit_notand(td,vu),tu);
    TTS_EQUAL(eve::bit_notand(td,vd),tz);
  }

  TTS_SUBCASE("wide<T> x wide<U> case")
  {
    TTS_EQUAL(eve::bit_notand(tu,uu),tz);
    TTS_EQUAL(eve::bit_notand(tu,ud),td);
    TTS_EQUAL(eve::bit_notand(td,uu),tu);
    TTS_EQUAL(eve::bit_notand(td,ud),tz);
  }

  TTS_SUBCASE("wide<T> x U case")
  {
    TTS_EQUAL(eve::bit_notand(tu,su),tz);
    TTS_EQUAL(eve::bit_notand(tu,sd),td);
    TTS_EQUAL(eve::bit_notand(td,su),tu);
    TTS_EQUAL(eve::bit_notand(td,sd),tz);
  }
}
