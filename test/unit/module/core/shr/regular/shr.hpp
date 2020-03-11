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

TTS_CASE("Check eve::shr return type")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using u_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;

  TTS_EXPR_IS(eve::shr(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::shr(EVE_TYPE(), i_t() ), (EVE_TYPE));
  TTS_EXPR_IS(eve::shr(EVE_TYPE(), u_t() ), (EVE_TYPE));
}

TTS_CASE("Check eve::shr behavior")
{
  TTS_EQUAL(eve::shr(EVE_TYPE( 0), 7), (EVE_TYPE(0)));
  TTS_EQUAL(eve::shr(EVE_TYPE(16), 4), (EVE_TYPE(1)));
  TTS_EQUAL(eve::shr(EVE_TYPE(12), 2), (EVE_TYPE(3)));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::shr(EVE_TYPE(-16), 4), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::shr(EVE_TYPE(-12), 2), (EVE_TYPE(-3)));
    TTS_EQUAL(eve::shr(eve::Allbits<EVE_TYPE>(), 1), eve::Allbits<EVE_TYPE>());
  }
  else
  {
    TTS_EQUAL(eve::shr(eve::Allbits<EVE_TYPE>(), 1), eve::Allbits<EVE_TYPE>()/2 );
  }
}
