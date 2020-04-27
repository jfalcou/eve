//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_UNORDERED_HPP
#define IS_UNORDERED_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_unordered.hpp>
#include <type_traits>

TTS_CASE_TPL("Check is_unordered return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_unordered(T(), T()), eve::as_logical_t<T>);
}

TTS_CASE_TPL("Check eve::is_unordered behavior on arithmetic", EVE_TYPE)
{
  TTS_EQUAL(eve::is_unordered(T(1), T(1)), eve::False<T>());
  TTS_EQUAL(eve::is_unordered(T(3), T(1)), eve::False<T>());
  TTS_EQUAL(eve::is_unordered(T(1), T(3)), eve::False<T>());

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_unordered(eve::Nan<T>(), T(3)), eve::True<T>());
    TTS_EQUAL(eve::is_unordered(T(3), eve::Nan<T>()), eve::True<T>());
    TTS_EQUAL(eve::is_unordered(eve::Nan<T>(), eve::Nan<T>()), eve::True<T>());
  }
}

#endif
