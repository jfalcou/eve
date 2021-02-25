//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/oneminus.hpp>
#include <eve/function/inc.hpp>

TTS_CASE_TPL("Check eve::saturated(eve::oneminus) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated(eve::oneminus)(T(1)), T(0));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(2)               ) , T(-1)           );
    TTS_EQUAL(eve::saturated(eve::oneminus)(static_cast<T>(-2) ) , T(3)            );
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::valmin(eve::as<T>())   ) , eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::inc(eve::valmin(eve::as<T>())))          , eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::saturated(eve::oneminus)(eve::inc(eve::inc(eve::valmin(eve::as<T>())))), eve::valmax(eve::as<T>()));
  }

  if constexpr(eve::unsigned_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(2)), T(0));
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(1)), T(0));
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(0)), T(1));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::oneminus)(T(-0.)), T(1));
    TTS_EQUAL(eve::saturated(eve::oneminus)(T( 0 )), T(1));
  }
}
