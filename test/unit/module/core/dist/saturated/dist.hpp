//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dist.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check saturated(eve::dist) return type")
{
  TTS_EXPR_IS(eve::saturated(eve::dist)(EVE_TYPE(), EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check saturated(eve::dist) behavior")
{
  TTS_EQUAL(eve::saturated(eve::dist)(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated(eve::dist)(EVE_TYPE(1), EVE_TYPE(5)), EVE_TYPE(4));

  if constexpr(eve::integral_value<EVE_TYPE>)
  {
    TTS_EQUAL ( eve::saturated(eve::dist)(eve::valmax(eve::as<EVE_TYPE>()),eve::valmin(eve::as<EVE_TYPE>()))
              , eve::valmax(eve::as<EVE_TYPE>())
              );

    if constexpr(eve::signed_value<EVE_TYPE>)
    {
      TTS_EQUAL(eve::saturated(eve::dist)(eve::valmin(eve::as<EVE_TYPE>()) , EVE_TYPE(-1)), eve::valmax(eve::as<EVE_TYPE>()));
      TTS_EQUAL(eve::saturated(eve::dist)(eve::valmin(eve::as<EVE_TYPE>()) , EVE_TYPE( 0)), eve::valmax(eve::as<EVE_TYPE>()));
      TTS_EQUAL(eve::saturated(eve::dist)(EVE_TYPE(-1) , EVE_TYPE( 1)), EVE_TYPE(2) );
      TTS_EQUAL(eve::saturated(eve::dist)(EVE_TYPE(-2) , EVE_TYPE(-6)), EVE_TYPE(4) );
    }
  }
}
