//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/shl.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/allbits.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::shl return type", EVE_TYPE)
{
  using i_t = eve::detail::as_integer_t<T, signed>;
  using u_t = eve::detail::as_integer_t<T, unsigned>;

  TTS_EXPR_IS(eve::shl(T(), T()), T);
  TTS_EXPR_IS(eve::shl(T(), i_t() ), T);
  TTS_EXPR_IS(eve::shl(T(), u_t() ), T);
}

TTS_CASE_TPL("Check eve::shl behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::shl(T(0), 7), (T( 0)));
  TTS_EQUAL(eve::shl(T(1), 4), (T(16)));
  TTS_EQUAL(eve::shl(T(3), 2), (T(12)));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::shl(T(-1), 4), (T(-16)));
    TTS_EQUAL(eve::shl(T(-3), 2), (T(-12)));
    TTS_EQUAL(eve::shl(eve::Allbits<T>(), 1), T(-2));
  }
  else
  {
    TTS_EQUAL(eve::shl(eve::Allbits<T>(), 1), eve::Allbits<T>() - 1 );
  }
}
