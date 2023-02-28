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

TTS_CASE_TPL( "Check three_pio_4 value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using doublereal_t   = eve::doublereal<T>;
   auto doublerealthree_pio_4 = eve::three_pio_4(eve::as<doublereal_t>());
   auto bmthree_pio_4 = 3*bm::atan(tts::uptype(eve::one(eve::as(doublerealthree_pio_4))));
   TTS_ULP_EQUAL(doublerealthree_pio_4, tts::to_doublereal<doublereal_t>(bmthree_pio_4), 0.5);

   TTS_LESS_EQUAL(eve::downward(eve::three_pio_4)(eve::as<doublereal_t>()), doublerealthree_pio_4);
   TTS_GREATER_EQUAL(eve::upward(eve::three_pio_4)(eve::as<doublereal_t>()), doublerealthree_pio_4);
};
