//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
#include <string>

TTS_CASE_TPL( "Check pio_2 value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using doublereal_t   = eve::doublereal<T>;
   auto doublerealpio_2 = eve::pio_2(eve::as<doublereal_t>());
   auto bmpio_2 = 2*bm::atan(tts::uptype(eve::one(eve::as(doublerealpio_2))));
   TTS_ULP_EQUAL(doublerealpio_2, tts::to_doublereal<doublereal_t>(bmpio_2), 0.5);

   TTS_LESS_EQUAL(eve::downward(eve::pio_2)(eve::as<doublereal_t>()), doublerealpio_2);
   TTS_GREATER_EQUAL(eve::upward(eve::pio_2)(eve::as<doublereal_t>()), doublerealpio_2);
};
