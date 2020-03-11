//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_shr.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::bit_shr return type")
{
  using ui_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  using si_t = eve::detail::as_integer_t<EVE_TYPE, signed>;

  TTS_EXPR_IS(eve::bit_shr(EVE_TYPE(), int()),  (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_shr(EVE_TYPE(), ui_t()), (EVE_TYPE));
  TTS_EXPR_IS(eve::bit_shr(EVE_TYPE(), si_t()), (EVE_TYPE));
}

TTS_CASE( "Check eve::bit_shr behavior")
{
  TTS_EQUAL(eve::bit_shr((EVE_TYPE(4)), 1), (EVE_TYPE(2)) );
  TTS_EQUAL(eve::bit_shr((EVE_TYPE(2)), 1), (EVE_TYPE(1)) );
  TTS_EQUAL(eve::bit_shr((EVE_TYPE(1)), 1), (EVE_TYPE(0)) );
  TTS_EQUAL(eve::bit_shr((EVE_TYPE(0)), 1), (EVE_TYPE(0)) );

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::bit_shr((EVE_TYPE(-1)),(sizeof(EVE_VALUE)*8-1)), (EVE_TYPE(1)));
    TTS_EQUAL(eve::bit_shr((EVE_TYPE(-1)),(sizeof(EVE_VALUE)*8-2)), (EVE_TYPE(3)));
  }
  else
  {
    TTS_EQUAL(eve::bit_shr(eve::Valmax<EVE_TYPE>(),(sizeof(EVE_VALUE)*8-1)), (EVE_TYPE(1)));
    TTS_EQUAL(eve::bit_shr(eve::Valmax<EVE_TYPE>(),(sizeof(EVE_VALUE)*8-2)), (EVE_TYPE(3)));
  }
}
