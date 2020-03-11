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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_or return type")
{
  using eve::detail::as_integer_t;
  using ui_t = as_integer_t<EVE_TYPE, unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS(eve::bit_or(EVE_TYPE(), EVE_TYPE()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_or(EVE_TYPE(), EVE_VALUE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_or(EVE_TYPE(), ui_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_or(EVE_TYPE(), vi_t()) , (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_or(ui_t(), EVE_TYPE()) , ui_t  );
}

TTS_CASE( "Check eve::bit_or behavior")
{
  using eve::detail::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using ui_t = as_integer_t<EVE_TYPE , unsigned>;
  using vi_t = as_integer_t<EVE_VALUE, unsigned>;

  constexpr auto u  = 0x5555555555555555ULL;

  auto tz = EVE_TYPE(0);
  auto vz = EVE_VALUE(0);

  ui_t uu( static_cast<vi_t>(u) );
  ui_t uz( static_cast<vi_t>(0) );
  auto tu = bit_cast(uu, as<EVE_TYPE>());

  vi_t su( static_cast<vi_t>(u) );
  auto vu = bit_cast(su, as<EVE_VALUE>());

  TTS_SUBCASE("wide<T> x wide<T> case")
  {
    TTS_EQUAL(eve::bit_or(tu,tu),tu);
    TTS_EQUAL(eve::bit_or(tu,tz),tu);
    TTS_EQUAL(eve::bit_or(tz,tu),tu);
    TTS_EQUAL(eve::bit_or(tz,tz),tz);
  }

  TTS_SUBCASE("wide<T> x T case")
  {
    TTS_EQUAL(eve::bit_or(tu,vu),tu);
    TTS_EQUAL(eve::bit_or(tu,vz),tu);
    TTS_EQUAL(eve::bit_or(tz,vu),tu);
    TTS_EQUAL(eve::bit_or(tz,vz),tz);
  }

  TTS_SUBCASE("wide<T> x wide<U> case")
  {
    TTS_EQUAL(eve::bit_or(tu,uu),tu);
    TTS_EQUAL(eve::bit_or(tu,uz),tu);
    TTS_EQUAL(eve::bit_or(tz,uu),tu);
    TTS_EQUAL(eve::bit_or(tz,uz),tz);
  }

  TTS_SUBCASE("wide<T> x U case")
  {
    TTS_EQUAL(eve::bit_or(tu,vu),tu);
    TTS_EQUAL(eve::bit_or(tu,vz),tu);
    TTS_EQUAL(eve::bit_or(tz,vu),tu);
    TTS_EQUAL(eve::bit_or(tz,vz),tz);
  }
}
