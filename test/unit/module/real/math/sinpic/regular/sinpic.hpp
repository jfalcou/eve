//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpic.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::sinpic return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinpic(T(0)), T);
}

TTS_CASE_TPL("Check eve::sinpic behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::sinpic(T(0)), T(1), 0.5);
  TTS_ULP_EQUAL(eve::sinpic(-T(1)/T(2)), T(2)/(eve::pi(eve::as<T>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(-T(1)/T(4)), eve::sinpi(T(1)/T(4))*T(4)/(eve::pi(eve::as<T>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(T(1)/T(2)),  T(2)/(eve::pi(eve::as<T>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(T(1)/T(4)), eve::sinpi(T(1)/T(4))*T(4)/(eve::pi(eve::as<T>())), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(eve::eps(eve::as<T>())), eve::one(eve::as<T>()), 1.0);
  TTS_ULP_EQUAL(eve::sinpic(eve::zero(eve::as<T>())), eve::one(eve::as<T>()), 1.0);

}
