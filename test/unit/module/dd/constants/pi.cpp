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

TTS_CASE_TPL( "Check pi value ", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
   using dd_t   = eve::dd<T>;
   using wdd_t  = eve::wide<dd_t>;
   auto ddpi = eve::pi(eve::as<dd_t>());
   auto bmpi = 4*bm::atan(tts::uptype(eve::one(eve::as(ddpi))));
   auto wddpi = eve::pi(eve::as<wdd_t>());
   TTS_ULP_EQUAL(ddpi, dd_t(bmpi), 0.5);
   TTS_ULP_EQUAL(wddpi, wdd_t(bmpi), 0.5);
};
