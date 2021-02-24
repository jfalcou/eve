//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::secpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::secpi(T()), T);
}

TTS_CASE_TPL("Check eve::secpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::secpi(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::secpi(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::secpi(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::secpi(T( 0 )) , T(1));
  TTS_IEEE_EQUAL(eve::secpi(T(-0.)) , T(1));

  TTS_ULP_EQUAL(eve::secpi(T(22.5)) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::secpi(-T(22.5)), eve::nan(eve::as<T>()) , 0.5);

  TTS_ULP_EQUAL(eve::secpi( T(1))         , T(-1), 0.5);
  TTS_ULP_EQUAL(eve::secpi(-T(1))         , T(-1), 0.5);
  TTS_ULP_EQUAL(eve::secpi( T(100000.0))  , T( 1), 0.5);
  TTS_ULP_EQUAL(eve::secpi(-T(100000.0))  , T( 1), 0.5);
  TTS_ULP_EQUAL(eve::secpi( T(1000001.0)) , T(-1), 0.5);
  TTS_ULP_EQUAL(eve::secpi(-T(1000001.0)) , T(-1), 0.5);

}
