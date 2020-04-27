//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef QUADRANT_HPP
#define QUADRANT_HPP

#include <eve/function/scalar/quadrant.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

TTS_CASE_TPL("Check quadrant return type", EVE_TYPE) { TTS_EXPR_IS(eve::quadrant(T(0)), T); }

TTS_CASE_TPL("Check eve::quadrant behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::quadrant(T(1)), T(1));
  TTS_EQUAL(eve::quadrant(T(2)), T(2));
  TTS_EQUAL(eve::quadrant(T(3)), T(3));
  TTS_EQUAL(eve::quadrant(T(4)), T(0));
  if constexpr(std::is_signed_v<T>)
  {
    TTS_EQUAL(eve::quadrant(T(-1)), T(3));
    TTS_EQUAL(eve::quadrant(T(-2)), T(2));
    TTS_EQUAL(eve::quadrant(T(-3)), T(1));
    TTS_EQUAL(eve::quadrant(T(-4)), T(0));
  }
}

#endif
