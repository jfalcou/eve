//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>
#include <string>

TTS_CASE_TPL( "Check pio_2 value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using dd_t   = eve::dd<T>;
   auto ddpio_2 = eve::pio_2(eve::as<dd_t>());
   auto bmpio_2 = 2*bm::atan(tts::uptype(eve::one(eve::as(ddpio_2))));
   TTS_ULP_EQUAL(ddpio_2, tts::to_dd<dd_t>(bmpio_2), 0.5);
};
