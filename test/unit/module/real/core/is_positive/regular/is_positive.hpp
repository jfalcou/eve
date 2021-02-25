//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_positive.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check is_positive return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_positive(T()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_positive behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_positive(T(-1)), eve::false_(eve::as<T>()));
  }
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_positive(T( 0 )), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_positive(T(-0.)), eve::false_(eve::as<T>()));
  }
  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_positive( eve::nan(eve::as<T>())), eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::is_positive(-eve::nan(eve::as<T>())), eve::true_(eve::as<T>())  );
  }
  TTS_EQUAL(eve::is_positive(T(0)), eve::true_(eve::as<T>()));
  TTS_EQUAL(eve::is_positive(T(3)), eve::true_(eve::as<T>()));
}
