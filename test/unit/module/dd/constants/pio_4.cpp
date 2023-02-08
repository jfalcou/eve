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

TTS_CASE_TPL( "Check pio_4 value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using dd_t   = eve::dd<T>;
   auto ddpio_4 = eve::pio_4(eve::as<dd_t>());
   auto bmpio_4 = bm::atan(tts::uptype(eve::one(eve::as(ddpio_4))));
   TTS_ULP_EQUAL(ddpio_4, tts::to_dd<dd_t>(bmpio_4), 0.5);
};
