//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqrt.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::sqrt return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sqrt(T(0)), T);
}

TTS_CASE_TPL("Check eve::sqrt behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::sqrt(T(-0.))   , (T(0)));
  TTS_EQUAL(eve::sqrt(T( 0))    , (T(0)));
  TTS_EQUAL(eve::sqrt(T( 1))    , (T(1)));
  TTS_EQUAL(eve::sqrt(T( 4))    , (T(2)));

  TTS_ULP_EQUAL(eve::sqrt(T(2)) , eve::sqrt_2(eve::as<T>()), 0.5);

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::sqrt(eve::nan(eve::as<T>())), (eve::nan(eve::as<T>())));
  }
}
