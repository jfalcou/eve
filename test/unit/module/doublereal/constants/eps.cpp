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

TTS_CASE_TPL( "Check eps value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using doublereal_t   = eve::doublereal<T>;
   auto doublerealeps = eve::eps(eve::as<doublereal_t>());

   TTS_EQUAL(eve::downward(eve::eps)(eve::as<doublereal_t>()), doublerealeps);
   TTS_EQUAL(eve::upward(eve::eps)(eve::as<doublereal_t>()), doublerealeps);
};
