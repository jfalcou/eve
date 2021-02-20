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

TTS_CASE_TPL("Check eve::bit_and return type", EVE_TYPE)
{
  using eve::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::bit_and(T()  , T()) , T);
  TTS_EXPR_IS(eve::bit_and(T()  , v_t()), T);
  TTS_EXPR_IS(eve::bit_and(v_t() , T()) , T);
  TTS_EXPR_IS(eve::bit_and(T()  , ui_t())     , T);
  TTS_EXPR_IS(eve::bit_and(T()  , vi_t())     , T);
  TTS_EXPR_IS(eve::bit_and(ui_t()      , T()) , ui_t      );
  TTS_EXPR_IS(eve::bit_and(vi_t()      , T()) , ui_t      );
}

TTS_CASE_TPL( "Check eve::bit_and behavior", EVE_TYPE)
{
  using eve::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;
  constexpr auto d  = 0xAAAAAAAAAAAAAAAAULL;

  auto tz = T(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t uz( static_cast<vi_t>(0) );
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bit_cast(ud, as<T>());
  auto tu = bit_cast(uu, as<T>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<v_t>());
  auto vd = bit_cast(sd, as<v_t>());

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
