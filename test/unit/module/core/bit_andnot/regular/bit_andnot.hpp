//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_andnot.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_andnot return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS(eve::bit_andnot(EVE_TYPE(), EVE_TYPE()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_andnot(EVE_TYPE(), EVE_VALUE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_andnot(EVE_TYPE(), ui_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_andnot(EVE_TYPE(), vi_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_andnot(ui_t(), EVE_TYPE()) , ui_t  );
}

TTS_CASE( "Check eve::bit_andnot behavior")
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
    TTS_EQUAL(eve::bit_andnot(tu,tu),tz);
    TTS_EQUAL(eve::bit_andnot(tu,td),tu);
    TTS_EQUAL(eve::bit_andnot(td,tu),td);
    TTS_EQUAL(eve::bit_andnot(td,td),tz);
  }

  TTS_SUBCASE("wide<T> x T case")
  {
    TTS_EQUAL(eve::bit_andnot(tu,vu),tz);
    TTS_EQUAL(eve::bit_andnot(tu,vd),tu);
    TTS_EQUAL(eve::bit_andnot(td,vu),td);
    TTS_EQUAL(eve::bit_andnot(td,vd),tz);
  }

  TTS_SUBCASE("wide<T> x wide<U> case")
  {
    TTS_EQUAL(eve::bit_andnot(tu,uu),tz);
    TTS_EQUAL(eve::bit_andnot(tu,ud),tu);
    TTS_EQUAL(eve::bit_andnot(td,uu),td);
    TTS_EQUAL(eve::bit_andnot(td,ud),tz);
  }

  TTS_SUBCASE("wide<T> x U case")
  {
    TTS_EQUAL(eve::bit_andnot(tu,su),tz);
    TTS_EQUAL(eve::bit_andnot(tu,sd),tu);
    TTS_EQUAL(eve::bit_andnot(td,su),td);
    TTS_EQUAL(eve::bit_andnot(td,sd),tz);
  }
}
