//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_denormal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/smallestposval.hpp>

TTS_CASE("Check eve::is_not_denormal return type")
{
  TTS_EXPR_IS(eve::is_not_denormal(EVE_TYPE()), eve::logical<EVE_TYPE>);
}

TTS_CASE_TPL("Check eve::is_not_denormal behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_denormal(T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_not_denormal(T(2)), eve::true_(eve::as<T>()));

  if constexpr(eve::platform::supports_denormals && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_not_denormal(eve::smallestposval(eve::as<T>()) / 2), eve::false_(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::is_not_denormal(eve::smallestposval(eve::as<T>()) / 2), eve::true_(eve::as<T>()));
  }
}
