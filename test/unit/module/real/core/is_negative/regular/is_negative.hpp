//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_negative.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE_TPL("Check eve::is_negative return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_negative(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_negative behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_negative(T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_negative(T(2)), eve::false_(eve::as<T>()));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_negative(T(-1)), eve::true_(eve::as<T>()));
  }
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_negative(T( 0 )), eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::is_negative(T(-0.)), eve::true_(eve::as<T>())  );

    if constexpr(eve::platform::supports_nans)
    {
      TTS_EQUAL(eve::is_negative(eve::nan(eve::as<T>())), eve::true_(eve::as<T>()));
    }
  }
}
