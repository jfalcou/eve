//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_real.hpp>

TTS_CASE_TPL("Check is_real return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_real(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_real behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_real(T{0}), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_real(T{2}), eve::true_(eve::as<T>()));
}
