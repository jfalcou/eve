//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_POSITIVE_HPP
#define IS_POSITIVE_HPP

#include <eve/function/is_positive.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/platform.hpp>
#include <type_traits>

TTS_CASE_TPL("Check is_positive return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_positive(T()), eve::as_logical_t<T>);
}

TTS_CASE_TPL("Check eve::is_positive behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_positive(T(-1)), eve::False<T>());
  }
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_positive(T( 0 )), eve::True<T>());
    TTS_EQUAL(eve::is_positive(T(-0.)), eve::False<T>());
  }
  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_positive(eve::Nan<T>()), eve::False<T>());
    TTS_EQUAL(eve::is_positive(-eve::Nan<T>()), eve::True<T>());
  }
  TTS_EQUAL(eve::is_positive(T(0)), eve::True<T>());
  TTS_EQUAL(eve::is_positive(T(3)), eve::True<T>());
}

#endif
