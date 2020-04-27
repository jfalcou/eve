//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_LESS_EQUAL_HPP
#define IS_NOT_LESS_EQUAL_HPP

#include <eve/function/is_not_less_equal.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE_TPL("Check is_not_less_equal return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_less_equal(T(), T()), eve::as_logical_t<T>);
}

TTS_CASE_TPL("Check eve::is_not_less_equal behavior", EVE_TYPE)
{
  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_not_less_equal(T(1), eve::Nan<T>()), eve::True<T>());
    TTS_EQUAL(eve::is_not_less_equal(eve::Nan<T>(), T(1)), eve::True<T>());
  }
  TTS_EQUAL(eve::is_not_less_equal(T(1), T(1)), eve::False<T>());
  TTS_EQUAL(eve::is_not_less_equal(T(3), T(1)), eve::True<T>());
  TTS_EQUAL(eve::is_not_less_equal(T(1), T(3)), eve::False<T>());
}

#endif
