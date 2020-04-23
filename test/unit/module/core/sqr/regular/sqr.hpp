//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::sqr return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sqr(T(0)), T);
}

TTS_CASE_TPL("Check eve::sqr behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::sqr(T(1)), T(1) );
  TTS_EQUAL(eve::sqr(T(2)), T(4) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::sqr(static_cast<T>(-2)), T(4));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::sqr(T(-0.)), T(0));
  }
}

