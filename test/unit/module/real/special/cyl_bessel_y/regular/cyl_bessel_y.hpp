//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/bessel.hpp>
#include <eve/function/cyl_bessel_y.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cyl_bessel_y return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cyl_bessel_y(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::cyl_bessel_y behavior", EVE_TYPE)
{

  auto eve__cyl_bessel_y =  [](auto n, auto x) { return eve::cyl_bessel_y(n, x); };
  auto boost_cyl_bessel_y =  [](auto n, auto x) { return boost::math::cyl_neumann(n, x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_y(T(2), eve::inf(eve::as<T>())), eve::zero(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__cyl_bessel_y(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  for(int i=1; i < 2; i*= 2)
  {
    TTS_ULP_EQUAL(eve__cyl_bessel_y(T(i), T(10)), T(boost_cyl_bessel_y(i, 10)), 10);
    TTS_ULP_EQUAL(eve__cyl_bessel_y(T(i), T(5)), T(boost_cyl_bessel_y(i, 5)), 10);
    TTS_ULP_EQUAL(eve__cyl_bessel_y(T(i), T(2)), T(boost_cyl_bessel_y(i, 2)), 10);
    TTS_ULP_EQUAL(eve__cyl_bessel_y(T(i), T(1)), T(boost_cyl_bessel_y(i, 1)), 10);
  }
}
