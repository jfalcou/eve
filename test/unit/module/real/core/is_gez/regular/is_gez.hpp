//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_gez.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::is_gez return type", EVE_TYPE)
{
  using eve::logical;
  TTS_EXPR_IS(eve::is_gez(T() ), logical<T>);
}

TTS_CASE_TPL("Check eve::is_gez behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_gez(T(-1)), eve::false_(eve::as<T>()));
  }

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_gez(eve::nan(eve::as<T>())), eve::false_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_gez(T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_gez(T(3)), eve::true_(eve::as<T>()));
}
