//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_ornot.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_ornot return type", EVE_TYPE)
{
  using eve::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::bit_ornot(T(), T()) , T);
  TTS_EXPR_IS(eve::bit_ornot(T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_ornot(T(), ui_t()) , T);
  TTS_EXPR_IS(eve::bit_ornot(T(), vi_t()) , T);
  TTS_EXPR_IS(eve::bit_ornot(ui_t(), T()) , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_ornot behavior", EVE_TYPE)
{
  using eve::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  constexpr auto u  = 0xAAAAAAAAAAAAAAAAULL;
  constexpr auto d  = 0x6666666666666666ULL;
  constexpr auto m  = 0x7777777777777777ULL;
  constexpr auto n  = 0xBBBBBBBBBBBBBBBBULL;

  ui_t uu( static_cast<vi_t>(u) );
  ui_t ud( static_cast<vi_t>(d) );
  ui_t um( static_cast<vi_t>(m) );
  ui_t un( static_cast<vi_t>(n) );
  auto td = bit_cast(ud, as<T>());
  auto tu = bit_cast(uu, as<T>());
  auto tm = bit_cast(um, as<T>());
  auto tn = bit_cast(un, as<T>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<v_t>());
  auto vd = bit_cast(sd, as<v_t>());

  TTS_EQUAL(eve::bit_ornot(tu,td),tn);
  TTS_EQUAL(eve::bit_ornot(td,tu),tm);
  TTS_EQUAL(eve::bit_ornot(tu,vd),tn);
  TTS_EQUAL(eve::bit_ornot(td,vu),tm);
  TTS_EQUAL(eve::bit_ornot(tu,ud),tn);
  TTS_EQUAL(eve::bit_ornot(td,uu),tm);
  TTS_EQUAL(eve::bit_ornot(tu,sd),tn);
  TTS_EQUAL(eve::bit_ornot(td,su),tm);
}
