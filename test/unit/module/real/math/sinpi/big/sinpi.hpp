//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::big(eve::sinpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big(eve::sinpi)(T(0)), T);
}

TTS_CASE_TPL("Check eve::big(eve::sinpi)behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::sinpi)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::big(eve::sinpi)(eve::inf(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::big(eve::sinpi)(eve::minf(eve::as<T>())), (eve::nan(eve::as<T>())) );
  }

  TTS_EXPECT(eve::all(eve::is_positive(eve::big(eve::sinpi)(T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::big(eve::sinpi)(T(-0.)))));

  TTS_IEEE_EQUAL(eve::big(eve::sinpi)(T( 0.)), T(0) );
  TTS_IEEE_EQUAL(eve::big(eve::sinpi)(T(-0.)), T(0) );

  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T(  1   )), T( 0), 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T(- 1   )), T( 0), 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T( 22.5 )), T( 1), 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T(-22.5 )), T(-1), 0.5);

  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T(     100000.0 )), T(0), 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T(-    100000.0 )), T(0), 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T(  100000000.0 )), T(0), 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sinpi)(T(- 100000000.0 )), T(0), 0.5);
}
