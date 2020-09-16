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

TTS_CASE_TPL("Check eve::bit_andnot return type", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::bit_andnot(T(), T()) , T);
  TTS_EXPR_IS(eve::bit_andnot(T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_andnot(T(), ui_t()) , T);
  TTS_EXPR_IS(eve::bit_andnot(T(), vi_t()) , T);
  TTS_EXPR_IS(eve::bit_andnot(ui_t(), T()) , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_andnot behavior", EVE_TYPE)
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T , unsigned>;
  using svi_t = as_integer_t<v_t, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;
  constexpr auto d  = 0xAAAAAAAAAAAAAAAAULL;

  auto tz = T(0);

  ui_t uu( static_cast<svi_t>(u) );
  ui_t uz( static_cast<svi_t>(0) );
  ui_t ud( static_cast<svi_t>(d) );
  auto td = bit_cast(ud, as<T>());
  auto tu = bit_cast(uu, as<T>());

  svi_t su( static_cast<svi_t>(u) );
  svi_t sd( static_cast<svi_t>(d) );
  auto vu = bit_cast(su, as<v_t>());
  auto vd = bit_cast(sd, as<v_t>());

  TTS_EQUAL(eve::bit_andnot(tu,tu),tz);
  TTS_EQUAL(eve::bit_andnot(tu,td),tu);
  TTS_EQUAL(eve::bit_andnot(td,tu),td);
  TTS_EQUAL(eve::bit_andnot(td,td),tz);

  TTS_EQUAL(eve::bit_andnot(tu,vu),tz);
  TTS_EQUAL(eve::bit_andnot(tu,vd),tu);
  TTS_EQUAL(eve::bit_andnot(td,vu),td);
  TTS_EQUAL(eve::bit_andnot(td,vd),tz);

  TTS_EQUAL(eve::bit_andnot(tu,uu),tz);
  TTS_EQUAL(eve::bit_andnot(tu,ud),tu);
  TTS_EQUAL(eve::bit_andnot(td,uu),td);
  TTS_EQUAL(eve::bit_andnot(td,ud),tz);

  TTS_EQUAL(eve::bit_andnot(tu,su),tz);
  TTS_EQUAL(eve::bit_andnot(tu,sd),tu);
  TTS_EQUAL(eve::bit_andnot(td,su),td);
  TTS_EQUAL(eve::bit_andnot(td,sd),tz);

  TTS_EQUAL(eve::bit_andnot(su,tu),uz);
  TTS_EQUAL(eve::bit_andnot(sd,tu),ud);
  TTS_EQUAL(eve::bit_andnot(su,td),uu);
  TTS_EQUAL(eve::bit_andnot(sd,td),uz);

}
