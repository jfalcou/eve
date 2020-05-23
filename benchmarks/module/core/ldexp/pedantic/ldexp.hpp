//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ldexp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <type_traits>

TTS_CASE("Check pedantic ldexp return type")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using u_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  using si_t = eve::detail::as_integer_t<EVE_VALUE, signed>;
  using su_t = eve::detail::as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS((eve::pedantic_(eve::ldexp)(EVE_TYPE(), i_t())), (EVE_TYPE));
  TTS_EXPR_IS((eve::pedantic_(eve::ldexp)(EVE_TYPE(), u_t())), (EVE_TYPE));
  TTS_EXPR_IS((eve::pedantic_(eve::ldexp)(EVE_TYPE(), si_t())), (EVE_TYPE));
  TTS_EXPR_IS((eve::pedantic_(eve::ldexp)(EVE_TYPE(), su_t())), (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::ldexp) two parameters behavior")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using si_t = eve::detail::as_integer_t<EVE_VALUE, signed>;

  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE{0}, i_t(2)), EVE_TYPE(0));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE{1}, i_t(2)), EVE_TYPE(4));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE{0}, si_t(2)),EVE_TYPE(0));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE{1}, si_t(2)),EVE_TYPE(4));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Valmax<EVE_TYPE>()/4, i_t(2)), eve::Valmax<EVE_TYPE>());
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Mindenormal <EVE_TYPE>(), i_t(2)), eve::Mindenormal<EVE_TYPE>()*4);

  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE{0.0}, i_t(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE{-0.0}, i_t(0)), EVE_TYPE(0));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic_(eve::ldexp)(EVE_TYPE(-0.0), i_t(0)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic_(eve::ldexp)(EVE_TYPE( 0.0), i_t(0)))));

  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE(1), i_t(2)), EVE_TYPE(4));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE(-2), i_t(2)), EVE_TYPE(-8));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE(-1), si_t(2)),EVE_TYPE(-4));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(EVE_TYPE(-2), si_t(2)),EVE_TYPE(-8));
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Valmax<EVE_TYPE>()/4, si_t(2)), eve::Valmax<EVE_TYPE>());
  TTS_EQUAL(eve::pedantic_(eve::ldexp)(eve::Mindenormal <EVE_TYPE>(), si_t(2)), eve::Mindenormal<EVE_TYPE>()*4);

}
