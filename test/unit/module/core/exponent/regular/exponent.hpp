//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exponent.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::exponent return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exponent(T(0)), eve::detail::as_integer_t<T>);
}

TTS_CASE_TPL("Check eve::exponent  behavior", EVE_TYPE)
{
  using r_t = eve::detail::as_integer_t<T>;

  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::exponent(eve::Inf<T>()) , r_t(0));
    TTS_EQUAL(eve::exponent(eve::Minf<T>()), r_t(0));
    TTS_EQUAL(eve::exponent(eve::Nan<T>()) , r_t(0));
  }

  TTS_EQUAL(eve::exponent(T(0   )), r_t(0));
  TTS_EQUAL(eve::exponent(T(1   )), r_t(0));
  TTS_EQUAL(eve::exponent(T(1.5 )), r_t(0));
  TTS_EQUAL(eve::exponent(T(2   )), r_t(1));
  TTS_EQUAL(eve::exponent(T(2.5 )), r_t(1));
  TTS_EQUAL(eve::exponent(T(4.5 )), r_t(2));
}

