//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acscpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::acscpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acscpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::acscpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acscpi(T(0))            , eve::nan(eve::as<T>()), 1);
    TTS_ULP_EQUAL(eve::acscpi(T(-0.)) , eve::nan(eve::as<T>()), 1);
    TTS_IEEE_EQUAL(eve::acscpi(eve::nan(eve::as<T>()))  , (eve::nan(eve::as<T>())) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::acscpi(eve::inf(eve::as<T>())) , (T(0)));
    TTS_IEEE_EQUAL(eve::acscpi(eve::minf(eve::as<T>())), (T(0)));
  }

  TTS_ULP_EQUAL(eve::acscpi(T(-2.)), T(-1)/6, 1.  );
  TTS_ULP_EQUAL(eve::acscpi(T( 2.)), T(1)/6 , 1.  );
  TTS_ULP_EQUAL(eve::acscpi(T(-1.)), T(-0.5), 0.5 );
  TTS_ULP_EQUAL(eve::acscpi(T( 1.)), T(0.5) , 0.5 );
}
