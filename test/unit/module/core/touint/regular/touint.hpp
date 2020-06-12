//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/touint.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::touint return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::touint(T(0)), (eve::detail::as_integer_t<T, unsigned>));
}

TTS_CASE_TPL("Check eve::touint behavior", EVE_TYPE)
{
  using r_t = eve::detail::as_integer_t<T, unsigned>;

  TTS_EQUAL(eve::touint(T( 1.2357)), static_cast<r_t>( 1.2357));
  TTS_EQUAL(eve::touint(T( 1))     , static_cast<r_t>( 1));
  TTS_EQUAL(eve::touint(T( 0))     , static_cast<r_t>( 0));

  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::touint(T(-0.)), r_t(0));
  }
  else if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(eve::touint(T(-47)), r_t(-47));
  }
}
