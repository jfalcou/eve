//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::asin return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asin(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::asin behavior", EVE_TYPE)
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asin(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::asin(T(2))          , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::asin(T(-2))         , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve::asin(T( 0.5)) ,  eve::pio_2(eve::as<T>())/3 , 0.5);
  TTS_ULP_EQUAL(eve::asin(T(-0.5)) , -eve::pio_2(eve::as<T>())/3 , 0.5);
  TTS_ULP_EQUAL(eve::asin(T(-1. )) , -eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(eve::asin(T( 1. )) ,  eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(eve::asin(T( 0. )) ,  T(0)              , 0.5);

  TTS_ULP_EQUAL(eve::asin(T(-0.)), T(0), 0.5);

  TTS_EXPECT( eve::all(is_negative(eve::asin(T(-0.)))) );
  TTS_EXPECT( eve::all(is_positive(eve::asin(T(0))))   );
}
