//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_ngtz.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::is_ngtz return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_ngtz(T() ), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_ngtz behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_ngtz(T(-1)), eve::true_(eve::as<T>()));
  }

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_ngtz(eve::nan(eve::as<T>())), eve::true_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_ngtz(T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_ngtz(T(3)), eve::false_(eve::as<T>()));
}
