//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_and.hpp>

TTS_CASE_TPL("Check operator& return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<T  , unsigned>;
  using vi_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(T()    & T()    , T   );
  TTS_EXPR_IS(T()    & v_t()  , T   );
  TTS_EXPR_IS(v_t()  & T()    , T   );
  TTS_EXPR_IS(T()    & ui_t() , T   );
  TTS_EXPR_IS(T()    & vi_t() , T   );
  TTS_EXPR_IS(ui_t() & T()    , ui_t);
  TTS_EXPR_IS(vi_t() & T()    , ui_t);
}

TTS_CASE_TPL( "Check operator& behavior", EVE_TYPE)
{
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<T , unsigned>;
  using vi_t = eve::as_integer_t<v_t, unsigned>;

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
  TTS_EQUAL((tu & tu),tu);
  TTS_EQUAL((tu & td),tz);
  TTS_EQUAL((td & tu),tz);
  TTS_EQUAL((td & td),td);

  // wT | T -> wT
  TTS_EQUAL((tu & vu),tu);
  TTS_EQUAL((tu & vd),tz);
  TTS_EQUAL((td & vu),tz);
  TTS_EQUAL((td & vd),td);

  // T | wT -> wT
  TTS_EQUAL((vu & tu),tu);
  TTS_EQUAL((vd & tu),tz);
  TTS_EQUAL((vu & td),tz);
  TTS_EQUAL((vd & td),td);

  // wT | wU -> wT
  TTS_EQUAL((tu & uu),tu);
  TTS_EQUAL((tu & ud),tz);
  TTS_EQUAL((td & uu),tz);
  TTS_EQUAL((td & ud),td);

  // wU | wT -> wU
  TTS_EQUAL((uu & tu),uu);
  TTS_EQUAL((ud & tu),uz);
  TTS_EQUAL((uu & td),uz);
  TTS_EQUAL((ud & td),ud);

  // wT | U -> wT
  TTS_EQUAL((tu & su),tu);
  TTS_EQUAL((tu & sd),tz);
  TTS_EQUAL((td & su),tz);
  TTS_EQUAL((td & sd),td);

  // U | wT -> wU
  TTS_EQUAL((su & tu),uu);
  TTS_EQUAL((sd & tu),uz);
  TTS_EQUAL((su & td),uz);
  TTS_EQUAL((sd & td),ud);
}
