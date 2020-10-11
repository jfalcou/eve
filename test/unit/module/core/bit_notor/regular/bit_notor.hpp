//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notor.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_notor return type", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::bit_notor(T(), T()) , T);
  TTS_EXPR_IS(eve::bit_notor(T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_notor(T(), ui_t()) , T);
  TTS_EXPR_IS(eve::bit_notor(T(), vi_t()) , T);
  TTS_EXPR_IS(eve::bit_notor(ui_t(), T()) , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_notor behavior", EVE_TYPE)
{
  using eve::detail::as_integer_t;
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

  TTS_EQUAL(eve::bit_notor(tu,td),tm);
  TTS_EQUAL(eve::bit_notor(td,tu),tn);

  TTS_EQUAL(eve::bit_notor(tu,vd),tm);
  TTS_EQUAL(eve::bit_notor(td,vu),tn);

  TTS_EQUAL(eve::bit_notor(tu,ud),tm);
  TTS_EQUAL(eve::bit_notor(td,uu),tn);

  TTS_EQUAL(eve::bit_notor(tu,sd),tm);
  TTS_EQUAL(eve::bit_notor(td,su),tn);
}
