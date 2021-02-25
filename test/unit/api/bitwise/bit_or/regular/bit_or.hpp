//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_and.hpp>

TTS_CASE_TPL("Check operator| return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<T  , unsigned>;
  using vi_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(T()    | T()    , T   );
  TTS_EXPR_IS(T()    | v_t()  , T   );
  TTS_EXPR_IS(v_t()  | T()    , T   );
  TTS_EXPR_IS(T()    | ui_t() , T   );
  TTS_EXPR_IS(T()    | vi_t() , T   );
  TTS_EXPR_IS(ui_t() | T()    , ui_t);
  TTS_EXPR_IS(vi_t() | T()    , ui_t);
}

TTS_CASE_TPL( "Check operator| behavior", EVE_TYPE)
{
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<T , unsigned>;
  using vi_t = eve::as_integer_t<v_t, unsigned>;

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
  TTS_EQUAL((tu | tu),tu);
  TTS_EQUAL((tu | tz),tu);
  TTS_EQUAL((tz | tu),tu);
  TTS_EQUAL((tz | tz),tz);

  // wT | T -> wT
  TTS_EQUAL((tu | vu),tu);
  TTS_EQUAL((tu | vz),tu);
  TTS_EQUAL((tz | vu),tu);
  TTS_EQUAL((tz | vz),tz);

  // T | wT -> wT
  TTS_EQUAL((vu | tu),tu);
  TTS_EQUAL((vz | tu),tu);
  TTS_EQUAL((vu | tz),tu);
  TTS_EQUAL((vz | tz),tz);

  // wT | wU -> wT
  TTS_EQUAL((tu | uu),tu);
  TTS_EQUAL((tu | uz),tu);
  TTS_EQUAL((tz | uu),tu);
  TTS_EQUAL((tz | uz),tz);

  // wU | wT -> wU
  TTS_EQUAL((uu | tu),uu);
  TTS_EQUAL((uz | tu),uu);
  TTS_EQUAL((uu | tz),uu);
  TTS_EQUAL((uz | tz),uz);

  // wT | U -> wT
  TTS_EQUAL((tu | su),tu);
  TTS_EQUAL((tu | sz),tu);
  TTS_EQUAL((tz | su),tu);
  TTS_EQUAL((tz | sz),tz);

  // U | wT -> wU
  TTS_EQUAL((su | tu),uu);
  TTS_EQUAL((sz | tu),uu);
  TTS_EQUAL((su | tz),uu);
  TTS_EQUAL((sz | tz),uz);
}
