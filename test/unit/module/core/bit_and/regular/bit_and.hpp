//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_and.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_and return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS(eve::bit_and(EVE_TYPE()  , EVE_TYPE()) , EVE_TYPE);
  TTS_EXPR_IS(eve::bit_and(EVE_TYPE()  , EVE_VALUE()), EVE_TYPE);
  TTS_EXPR_IS(eve::bit_and(EVE_VALUE() , EVE_TYPE()) , EVE_TYPE);
  TTS_EXPR_IS(eve::bit_and(EVE_TYPE()  , ui_t())     , EVE_TYPE);
  TTS_EXPR_IS(eve::bit_and(EVE_TYPE()  , vi_t())     , EVE_TYPE);
  TTS_EXPR_IS(eve::bit_and(ui_t()      , EVE_TYPE()) , ui_t      );
  TTS_EXPR_IS(eve::bit_and(vi_t()      , EVE_TYPE()) , ui_t      );
}

TTS_CASE( "Check eve::bit_and behavior")
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
  ui_t uz( static_cast<vi_t>(0) );
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bit_cast(ud, as<EVE_TYPE>());
  auto tu = bit_cast(uu, as<EVE_TYPE>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<EVE_VALUE>());
  auto vd = bit_cast(sd, as<EVE_VALUE>());

  // wT | wT -> wT
  TTS_EQUAL(eve::bit_and(tu,tu),tu);
  TTS_EQUAL(eve::bit_and(tu,td),tz);
  TTS_EQUAL(eve::bit_and(td,tu),tz);
  TTS_EQUAL(eve::bit_and(td,td),td);

  // wT | T -> wT
  TTS_EQUAL(eve::bit_and(tu,vu),tu);
  TTS_EQUAL(eve::bit_and(tu,vd),tz);
  TTS_EQUAL(eve::bit_and(td,vu),tz);
  TTS_EQUAL(eve::bit_and(td,vd),td);

  // T | wT -> wT
  TTS_EQUAL(eve::bit_and(vu,tu),tu);
  TTS_EQUAL(eve::bit_and(vd,tu),tz);
  TTS_EQUAL(eve::bit_and(vu,td),tz);
  TTS_EQUAL(eve::bit_and(vd,td),td);

  // wT | wU -> wT
  TTS_EQUAL(eve::bit_and(tu,uu),tu);
  TTS_EQUAL(eve::bit_and(tu,ud),tz);
  TTS_EQUAL(eve::bit_and(td,uu),tz);
  TTS_EQUAL(eve::bit_and(td,ud),td);

  // wU | wT -> wU
  TTS_EQUAL(eve::bit_and(uu,tu),uu);
  TTS_EQUAL(eve::bit_and(ud,tu),uz);
  TTS_EQUAL(eve::bit_and(uu,td),uz);
  TTS_EQUAL(eve::bit_and(ud,td),ud);

  // wT | U -> wT
  TTS_EQUAL(eve::bit_and(tu,su),tu);
  TTS_EQUAL(eve::bit_and(tu,sd),tz);
  TTS_EQUAL(eve::bit_and(td,su),tz);
  TTS_EQUAL(eve::bit_and(td,sd),td);

  // U | wT -> wU
  TTS_EQUAL(eve::bit_and(su,tu),uu);
  TTS_EQUAL(eve::bit_and(sd,tu),uz);
  TTS_EQUAL(eve::bit_and(su,td),uz);
  TTS_EQUAL(eve::bit_and(sd,td),ud);
}
