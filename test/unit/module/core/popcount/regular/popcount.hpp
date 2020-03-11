//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/sequence.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::popcount return type")
{
  TTS_EXPR_IS(eve::popcount(EVE_TYPE(0)), (eve::detail::as_integer_t<EVE_TYPE, unsigned>));
}

TTS_CASE("Check eve::popcount behavior")
{
  using r_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>; 
  TTS_EQUAL(eve::popcount( EVE_TYPE(0)), (eve::Zero<r_t>()));
  TTS_EQUAL(eve::popcount( EVE_TYPE(1)), (r_t(1))          );
  TTS_EQUAL(eve::popcount( EVE_TYPE(2)), (r_t(1))          );
  TTS_EQUAL(eve::popcount( EVE_TYPE(3)), (r_t(2))          );
  TTS_EQUAL(eve::popcount( EVE_TYPE(11)), (r_t(3))          );
  TTS_EQUAL(eve::popcount( eve::Valmax<EVE_TYPE>()), r_t(sizeof(EVE_VALUE)*8-std::is_signed_v<EVE_VALUE>)); 
}
