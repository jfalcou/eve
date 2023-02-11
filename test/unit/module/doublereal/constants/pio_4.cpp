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

TTS_CASE_TPL( "Check pio_4 value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using doublereal_t   = eve::doublereal<T>;
   auto doublerealpio_4 = eve::pio_4(eve::as<doublereal_t>());
   auto bmpio_4 = bm::atan(tts::uptype(eve::one(eve::as(doublerealpio_4))));
   TTS_ULP_EQUAL(doublerealpio_4, tts::to_doublereal<doublereal_t>(bmpio_4), 0.5);
};
