//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tofloat.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::tofloat return type", EVE_TYPE)
{
  TTS_EXPR_IS( eve::tofloat(T()), (eve::detail::as_floating_point_t<T>));
}

TTS_CASE_TPL("Check eve::tofloat behavior", EVE_TYPE)
{
  using r_t = eve::detail::as_floating_point_t<T>;

  if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(eve::tofloat(T(-2)), r_t(-2));
  }

  TTS_EQUAL(eve::tofloat(T(0)), r_t( 0));
  TTS_EQUAL(eve::tofloat(T(2)), r_t( 2));
}
