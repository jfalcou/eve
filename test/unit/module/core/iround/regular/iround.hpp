//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/iround.hpp>
#include <eve/function/inearest.hpp>
#include <eve/function/ifloor.hpp>
#include <eve/function/itrunc.hpp>
#include <eve/function/iceil.hpp>
#include <eve/function/roundings.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::upward_(eve::iround) return type")
{
  TTS_EXPR_IS(eve::upward_(eve::iround)(EVE_TYPE(0)), (eve::detail::as_integer_t<EVE_TYPE>));
}

TTS_CASE("Check eve::upward_(eve::iround) behavior")
{
  TTS_EQUAL(eve::upward_(eve::iround)((EVE_TYPE(1.7))), eve::iceil   ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::downward_(eve::iround)((EVE_TYPE(1.7))), eve::ifloor  ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::toward_zero_(eve::iround)((EVE_TYPE(1.7))), eve::itrunc  ((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::to_nearest_(eve::iround)((EVE_TYPE(1.7))), eve::inearest((EVE_TYPE(1.7))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.7))), eve::inearest((EVE_TYPE(1.7))) );

  TTS_EQUAL(eve::upward_(eve::iround)((EVE_TYPE(1.3))), eve::iceil   ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::downward_(eve::iround)((EVE_TYPE(1.3))), eve::ifloor  ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::toward_zero_(eve::iround)((EVE_TYPE(1.3))), eve::itrunc  ((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::to_nearest_(eve::iround)((EVE_TYPE(1.3))), eve::inearest((EVE_TYPE(1.3))) );
  TTS_EQUAL(eve::iround((EVE_TYPE(1.3))), eve::inearest((EVE_TYPE(1.3))) );
}
