//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_imag.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::is_not_imag return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_imag(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_imag behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_imag(T(0)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_not_imag(T(2)), eve::true_(eve::as<T>())  );
}
