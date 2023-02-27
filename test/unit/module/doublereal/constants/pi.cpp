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

TTS_CASE_TPL( "Check pi value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using doublereal_t   = eve::doublereal<T>;
   auto doublerealpi = eve::pi(eve::as<doublereal_t>());
   auto bmpi = 4*bm::atan(tts::uptype(eve::one(eve::as(doublerealpi))));
   TTS_ULP_EQUAL(doublerealpi, tts::to_doublereal<doublereal_t>(bmpi), 0.5);

   TTS_LESS_EQUAL(eve::downward(eve::pi)(eve::as<doublereal_t>()), doublerealpi);
   TTS_GREATER_EQUAL(eve::upward(eve::pi)(eve::as<doublereal_t>()), doublerealpi);
};
