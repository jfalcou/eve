//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_less_equal.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check is_not_less_equal return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_less_equal(T(), T()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_less_equal behavior", EVE_TYPE)
{
  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_not_less_equal(T(1)         , eve::nan(eve::as<T>()) ), eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::is_not_less_equal(eve::nan(eve::as<T>()), T(1)          ), eve::true_(eve::as<T>()));
  }

  TTS_EQUAL(eve::is_not_less_equal(T(1), T(1)), eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::is_not_less_equal(T(3), T(1)), eve::true_(eve::as<T>())  );
  TTS_EQUAL(eve::is_not_less_equal(T(1), T(3)), eve::false_(eve::as<T>()) );
}
