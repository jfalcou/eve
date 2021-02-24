//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecd.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::asecd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asecd(T(0)), T);
}

TTS_CASE_TPL("Check eve::asecd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asecd(eve::inf(eve::as<T>())) , (T(90)), 0.5);
    TTS_ULP_EQUAL(eve::asecd(eve::minf(eve::as<T>())), (T(90)), 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asecd(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_ULP_EQUAL(eve::asecd(T(0))  , eve::nan(eve::as<T>()), 1);
    TTS_ULP_EQUAL(eve::asecd(T(-0.)), eve::nan(eve::as<T>()), 1);
  }

  TTS_ULP_EQUAL(eve::asecd(T(-2.)), T(360)/3 , 1   );
  TTS_ULP_EQUAL(eve::asecd(T( 2.)), T(180)/3 , 1   );
  TTS_ULP_EQUAL(eve::asecd(T(-1.)), T(180)   , 0.5 );
  TTS_ULP_EQUAL(eve::asecd(T( 1.)), T(0)     , 0.5 );
}
