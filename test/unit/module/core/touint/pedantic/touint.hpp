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
  TTS_EXPR_IS(eve::pedantic_(eve::touint)(T(0)), (eve::detail::as_integer_t<T, unsigned>));
}

TTS_CASE_TPL("Check eve::pedantic_(eve::touint) behavior", EVE_TYPE)
{
  using r_t = eve::detail::as_integer_t<T, unsigned>;

  TTS_EQUAL(eve::pedantic_(eve::touint)(T( 1.2357)), static_cast<r_t>( 1.2357));
  TTS_EQUAL(eve::pedantic_(eve::touint)(T( 1))     , static_cast<r_t>( 1));
  TTS_EQUAL(eve::pedantic_(eve::touint)(T( 0))     , static_cast<r_t>( 0));

  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::pedantic_(eve::touint)(T(-0.)), r_t(0));
  }
  using elt_t = eve::element_type_t<T>;
  if constexpr( std::is_same_v<elt_t, float> )
  {
    TTS_EQUAL(eve::pedantic_(eve::touint)(T(+2.055783936e+09)), r_t(2055783936));
  }
}
