//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/dist.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check saturated(eve::dist) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated(eve::dist)(T(), T()), T);
}

TTS_CASE_TPL("Check saturated(eve::dist) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated(eve::dist)(T(0), T(0)), T(0));
  TTS_EQUAL(eve::saturated(eve::dist)(T(1), T(5)), T(4));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL ( eve::saturated(eve::dist)(eve::valmax(eve::as<T>()),eve::valmin(eve::as<T>()))
              , eve::valmax(eve::as<T>())
              );

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::saturated(eve::dist)(eve::valmin(eve::as<T>()) , T(-1)), eve::valmax(eve::as<T>()));
      TTS_EQUAL(eve::saturated(eve::dist)(eve::valmin(eve::as<T>()) , T( 0)), eve::valmax(eve::as<T>()));
      TTS_EQUAL(eve::saturated(eve::dist)(T(-1)            , T( 1)), T(2)            );
      TTS_EQUAL(eve::saturated(eve::dist)(T(-2)            , T(-6)), T(4)            );
    }
  }
}
