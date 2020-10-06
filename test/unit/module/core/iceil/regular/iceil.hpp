//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil.hpp>

TTS_CASE("Check iceil return type")
{
  TTS_EXPR_IS(eve::int_(eve::ceil)(EVE_TYPE()), eve::detail::as_integer_t<EVE_TYPE>);
}

TTS_CASE("Check eve::iceil behavior")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE>;

  TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(0)), i_t(0));
  TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(1)), i_t(1));
  TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(2)), i_t(2));

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(-1)), i_t(-1));
    TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(-2)), i_t(-2));
  }

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
   TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(-1.3)), i_t(-1));
   TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(-1.5)), i_t(-1));
   TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE(-1.6)), i_t(-1));
   TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE( 1.3)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE( 1.5)) , i_t( 2));
   TTS_EQUAL(eve::int_(eve::ceil)(EVE_TYPE( 1.6)) , i_t( 2));
  }
}
