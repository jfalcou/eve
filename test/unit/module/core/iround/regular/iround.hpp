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

TTS_CASE_TPL("Check eve::upward_(eve::iround) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::upward_(eve::iround)(T(0)), (eve::detail::as_integer_t<T>));
}

TTS_CASE_TPL("Check eve::upward_(eve::iround) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::upward_(eve::iround)((T(1.7))), eve::iceil   ((T(1.7))) );
  TTS_EQUAL(eve::downward_(eve::iround)((T(1.7))), eve::ifloor  ((T(1.7))) );
  TTS_EQUAL(eve::toward_zero_(eve::iround)((T(1.7))), eve::itrunc  ((T(1.7))) );
  TTS_EQUAL(eve::to_nearest_(eve::iround)((T(1.7))), eve::inearest((T(1.7))) );
  TTS_EQUAL(eve::iround((T(1.7))), eve::inearest((T(1.7))) );

  TTS_EQUAL(eve::upward_(eve::iround)((T(1.3))), eve::iceil   ((T(1.3))) );
  TTS_EQUAL(eve::downward_(eve::iround)((T(1.3))), eve::ifloor  ((T(1.3))) );
  TTS_EQUAL(eve::toward_zero_(eve::iround)((T(1.3))), eve::itrunc  ((T(1.3))) );
  TTS_EQUAL(eve::to_nearest_(eve::iround)((T(1.3))), eve::inearest((T(1.3))) );
  TTS_EQUAL(eve::iround((T(1.3))), eve::inearest((T(1.3))) );
}
