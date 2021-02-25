//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_denormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check eve::is_denormal return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_denormal(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_denormal behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_denormal(T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_denormal(T(2)), eve::false_(eve::as<T>()));

  if constexpr(eve::platform::supports_denormals && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_denormal(eve::smallestposval(eve::as<T>()) / 2), eve::true_(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::is_denormal(eve::smallestposval(eve::as<T>()) / 2), eve::false_(eve::as<T>()));
  }
}
