//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <eve/function/inc.hpp>

TTS_CASE("Check eve::saturated(eve::oneminus) behavior")
{
  TTS_EQUAL(eve::saturated(eve::oneminus)(EVE_TYPE(1)), EVE_TYPE(0));

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(EVE_TYPE(2)               ) , EVE_TYPE(-1)           );
    TTS_EQUAL(eve::saturated(eve::oneminus)(static_cast<EVE_TYPE>(-2) ) , EVE_TYPE(3)            );
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::valmin(eve::as<EVE_TYPE>())   ) , eve::valmax(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::inc(eve::valmin(eve::as<EVE_TYPE>())))          , eve::valmax(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::inc(eve::inc(eve::valmin(eve::as<EVE_TYPE>())))), eve::valmax(eve::as<EVE_TYPE>()));
  }

  if constexpr(eve::unsigned_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(EVE_TYPE(2)), EVE_TYPE(0));
    TTS_EQUAL(eve::saturated(eve::oneminus)(EVE_TYPE(1)), EVE_TYPE(0));
    TTS_EQUAL(eve::saturated(eve::oneminus)(EVE_TYPE(0)), EVE_TYPE(1));
  }

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(EVE_TYPE(-0.)), EVE_TYPE(1));
    TTS_EQUAL(eve::saturated(eve::oneminus)(EVE_TYPE( 0 )), EVE_TYPE(1));
  }
}
