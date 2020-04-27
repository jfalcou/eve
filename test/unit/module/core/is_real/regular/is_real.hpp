//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_REAL_HPP
#define IS_REAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_real.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

TTS_CASE_TPL("Check is_real return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_real(T(0)), eve::as_logical_t<T>);
}

TTS_CASE_TPL("Check eve::is_real behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_real(T{0}), eve::True<T>());
  TTS_EQUAL(eve::is_real(T{2}), eve::True<T>());
}

#endif
