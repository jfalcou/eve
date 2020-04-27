//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/shr.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::shr return type", EVE_TYPE)
{
  using i_t = eve::detail::as_integer_t<T, signed>;
  using u_t = eve::detail::as_integer_t<T, unsigned>;

  TTS_EXPR_IS(eve::shr(T(), T()), T);
  TTS_EXPR_IS(eve::shr(T(), i_t() ), T);
  TTS_EXPR_IS(eve::shr(T(), u_t() ), T);
}

TTS_CASE_TPL("Check eve::shr behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::shr(T( 0), 7), (T(0)));
  TTS_EQUAL(eve::shr(T(16), 4), (T(1)));
  TTS_EQUAL(eve::shr(T(12), 2), (T(3)));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::shr(T(-16), 4), (T(-1)));
    TTS_EQUAL(eve::shr(T(-12), 2), (T(-3)));
    TTS_EQUAL(eve::shr(eve::Allbits<T>(), 1), eve::Allbits<T>());
  }
  else
  {
    TTS_EQUAL(eve::shr(eve::Allbits<T>(), 1), eve::Allbits<T>()/2 );
  }
}
