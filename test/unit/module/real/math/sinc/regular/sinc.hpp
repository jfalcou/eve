//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinc.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::sinc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sinc(T(0)), T);
}

TTS_CASE_TPL("Check eve::sinc behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::sinc(T(0)), T(1), 0.5);
  TTS_ULP_EQUAL(eve::sinc(-eve::pio_2(eve::as<T>())), T(2)/(eve::pi(eve::as<T>())), 0.5);
  TTS_ULP_EQUAL(eve::sinc(-eve::pio_4(eve::as<T>())), eve::sin(eve::pio_4(eve::as<T>()))/(eve::pio_4(eve::as<T>())), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::pio_2(eve::as<T>())),  T(2)/(eve::pi(eve::as<T>())), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::pio_4(eve::as<T>())), eve::sin(eve::pio_4(eve::as<T>()))/(eve::pio_4(eve::as<T>())), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::eps(eve::as<T>())), eve::one(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::sinc(eve::zero(eve::as<T>())), eve::one(eve::as<T>()), 0.5);
}
