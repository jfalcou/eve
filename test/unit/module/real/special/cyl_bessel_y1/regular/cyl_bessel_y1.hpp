//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cyl_bessel_y1.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cyl_bessel_y1 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cyl_bessel_y1(T(0)), T);
}

TTS_CASE_TPL("Check eve::cyl_bessel_y1 behavior", EVE_TYPE)
{

  auto eve__cyl_bessel_y1 =  [](auto x) { return eve::cyl_bessel_y1(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y1(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(T(10)), T(  2.490154242069539e-01), 2.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(T(5)), T(1.478631433912269e-01), 1.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(T(2)), T( -1.070324315409375e-01), 4.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(T(1.5)), T(  -4.123086269739113e-01), 0.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(T(1)), T( -7.812128213002889e-01), 0.5);
  TTS_ULP_EQUAL(eve__cyl_bessel_y1(T(0)), eve::minf(eve::as<T>()), 0);
}
