//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_ODD_HPP
#define IS_ODD_HPP

#include <eve/function/is_odd.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

TTS_CASE_TPL("Check is_odd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_odd(T(0)), eve::as_logical_t<T>);
}

TTS_CASE_TPL("Check eve::is_odd behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_odd(T{1}), eve::True<T>());
  TTS_EQUAL(eve::is_odd(T{2}), eve::False<T>());
  TTS_EQUAL(eve::is_odd(T{3}), eve::True<T>());
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_odd(eve::Half<T>()), eve::False<T>());
    TTS_EQUAL(eve::is_odd(T(-0.)), eve::False<T>());
  }
}

#endif
