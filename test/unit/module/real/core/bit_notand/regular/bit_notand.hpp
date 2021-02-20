//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_notand.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_notand return type", EVE_TYPE)
{
  using eve::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::bit_notand(T(), T()) , T);
  TTS_EXPR_IS(eve::bit_notand(T(), v_t()), T);
  TTS_EXPR_IS(eve::bit_notand(T(), ui_t()) , T);
  TTS_EXPR_IS(eve::bit_notand(T(), vi_t()) , T);
  TTS_EXPR_IS(eve::bit_notand(ui_t(), T()) , ui_t  );
}

TTS_CASE_TPL( "Check eve::bit_notand behavior", EVE_TYPE)
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
  ui_t ud( static_cast<vi_t>(d) );
  auto td = bit_cast(ud, as<T>());
  auto tu = bit_cast(uu, as<T>());

  vi_t su( static_cast<vi_t>(u) );
  vi_t sd( static_cast<vi_t>(d) );
  auto vu = bit_cast(su, as<v_t>());
  auto vd = bit_cast(sd, as<v_t>());

  TTS_EQUAL(eve::bit_notand(tu,tu),tz);
  TTS_EQUAL(eve::bit_notand(tu,td),td);
  TTS_EQUAL(eve::bit_notand(td,tu),tu);
  TTS_EQUAL(eve::bit_notand(td,td),tz);

  TTS_EQUAL(eve::bit_notand(tu,vu),tz);
  TTS_EQUAL(eve::bit_notand(tu,vd),td);
  TTS_EQUAL(eve::bit_notand(td,vu),tu);
  TTS_EQUAL(eve::bit_notand(td,vd),tz);

  TTS_EQUAL(eve::bit_notand(tu,uu),tz);
  TTS_EQUAL(eve::bit_notand(tu,ud),td);
  TTS_EQUAL(eve::bit_notand(td,uu),tu);
  TTS_EQUAL(eve::bit_notand(td,ud),tz);

  TTS_EQUAL(eve::bit_notand(tu,su),tz);
  TTS_EQUAL(eve::bit_notand(tu,sd),td);
  TTS_EQUAL(eve::bit_notand(td,su),tu);
  TTS_EQUAL(eve::bit_notand(td,sd),tz);
}
