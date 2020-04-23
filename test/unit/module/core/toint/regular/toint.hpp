//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/toint.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::toint return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::toint(T(0)), (eve::detail::as_integer_t<T>));
}

TTS_CASE_TPL("Check eve::toint behavior", EVE_TYPE)
{
  using r_t = eve::detail::as_integer_t<T>;

  TTS_EQUAL(eve::toint(T(1.2357)), static_cast<r_t>(1.2357));
  TTS_EQUAL(eve::toint(T(1))     , r_t(1));
  TTS_EQUAL(eve::toint(T(0))     , r_t(0));

  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::toint(T(-0.)), r_t(0));
  }
}
