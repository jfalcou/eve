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

TTS_CASE_TPL( "Check smallestposval value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using doublereal_t   = eve::doublereal<T>;
   auto doublerealsmallestposval = eve::smallestposval(eve::as<doublereal_t>());

   TTS_EQUAL(eve::downward(eve::smallestposval)(eve::as<doublereal_t>()), doublerealsmallestposval);
   TTS_EQUAL(eve::upward(eve::smallestposval)(eve::as<doublereal_t>()), doublerealsmallestposval);
};
