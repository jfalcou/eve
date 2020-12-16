//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_imag.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::is_imag return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_imag(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_imag behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_imag(T(0)), eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::is_imag(T(2)), eve::false_(eve::as<T>()) );
}
