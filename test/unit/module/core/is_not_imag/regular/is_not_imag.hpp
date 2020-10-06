//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_imag.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE("Check eve::is_not_imag return type")
{
  TTS_EXPR_IS(eve::is_not_imag(EVE_TYPE(0)), eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::is_not_imag behavior")
{
  TTS_EQUAL(eve::is_not_imag(EVE_TYPE(0)), eve::false_(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::is_not_imag(EVE_TYPE(2)), eve::true_(eve::as<EVE_TYPE>())  );
}
