//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_or.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_or return type", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::bit_or(T()  , T()) , T);
  TTS_EXPR_IS(eve::bit_or(T()  , v_t()), T);
  TTS_EXPR_IS(eve::bit_or(v_t() , T()) , T);
  TTS_EXPR_IS(eve::bit_or(T()  , ui_t())     , T);
  TTS_EXPR_IS(eve::bit_or(T()  , vi_t())     , T);
  TTS_EXPR_IS(eve::bit_or(ui_t()      , T()) , ui_t      );
  TTS_EXPR_IS(eve::bit_or(vi_t()      , T()) , ui_t      );
}

TTS_CASE_TPL( "Check eve::bit_or behavior", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;

  auto tz = T(0);
  auto vz = v_t(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t uz( static_cast<vi_t>(0) );
  auto tu = bit_cast(uu, as<T>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sz( static_cast<vi_t>(0) );
  auto vu = bit_cast(su, as<v_t>());

  // wT | wT -> wT
  TTS_EQUAL(eve::bit_or(tu,tu),tu);
  TTS_EQUAL(eve::bit_or(tu,tz),tu);
  TTS_EQUAL(eve::bit_or(tz,tu),tu);
  TTS_EQUAL(eve::bit_or(tz,tz),tz);

  // wT | T -> wT
  TTS_EQUAL(eve::bit_or(tu,vu),tu);
  TTS_EQUAL(eve::bit_or(tu,vz),tu);
  TTS_EQUAL(eve::bit_or(tz,vu),tu);
  TTS_EQUAL(eve::bit_or(tz,vz),tz);

  // T | wT -> wT
  TTS_EQUAL(eve::bit_or(vu,tu),tu);
  TTS_EQUAL(eve::bit_or(vz,tu),tu);
  TTS_EQUAL(eve::bit_or(vu,tz),tu);
  TTS_EQUAL(eve::bit_or(vz,tz),tz);

  // wT | wU -> wT
  TTS_EQUAL(eve::bit_or(tu,uu),tu);
  TTS_EQUAL(eve::bit_or(tu,uz),tu);
  TTS_EQUAL(eve::bit_or(tz,uu),tu);
  TTS_EQUAL(eve::bit_or(tz,uz),tz);

  // wU | wT -> wU
  TTS_EQUAL(eve::bit_or(uu,tu),uu);
  TTS_EQUAL(eve::bit_or(uz,tu),uu);
  TTS_EQUAL(eve::bit_or(uu,tz),uu);
  TTS_EQUAL(eve::bit_or(uz,tz),uz);

  // wT | U -> wT
  TTS_EQUAL(eve::bit_or(tu,su),tu);
  TTS_EQUAL(eve::bit_or(tu,sz),tu);
  TTS_EQUAL(eve::bit_or(tz,su),tu);
  TTS_EQUAL(eve::bit_or(tz,sz),tz);

  // U | wT -> wU
  TTS_EQUAL(eve::bit_or(su,tu),uu);
  TTS_EQUAL(eve::bit_or(sz,tu),uu);
  TTS_EQUAL(eve::bit_or(su,tz),uu);
  TTS_EQUAL(eve::bit_or(sz,tz),uz);
}
