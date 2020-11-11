//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ellint_d.hpp>
#include <boost/math/special_functions/ellint_d.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::ellint_d return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::ellint_d(T(0)), T);
}

TTS_CASE_TPL("Check eve::ellint_d behavior one parameter", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::ellint_d(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::ellint_d(T(1)) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::ellint_d(T(-1)), eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL( eve::ellint_d(T( 0.)), T(boost::math::ellint_d(v_t(0))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_d(T( 0.5)), T(boost::math::ellint_d(v_t(0.5))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_d(T( 0.9)), T(boost::math::ellint_d(v_t(0.9))), 1.0);

}

TTS_CASE_TPL("Check eve::ellint_d behavior two parameter", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::ellint_d(eve::pio_2(as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL( eve::ellint_d(eve::pio_2(as<T>()), T( 0.)),  T(boost::math::ellint_d(v_t(0)  , eve::pio_2(as<v_t>()))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_d(eve::pio_2(as<T>()), T( 0.5)), T(boost::math::ellint_d(v_t(0.5), eve::pio_2(as<v_t>()))), 1.5);
  TTS_ULP_EQUAL( eve::ellint_d(eve::pio_2(as<T>()), T( 0.9)), T(boost::math::ellint_d(v_t(0.9), eve::pio_2(as<v_t>()))), 2.5);
  TTS_ULP_EQUAL( eve::ellint_d(eve::pio_4(as<T>()), T( 0.)),  T(boost::math::ellint_d(v_t(0)  , eve::pio_4(as<v_t>()))), 1.5);
  TTS_ULP_EQUAL( eve::ellint_d(eve::pio_4(as<T>()), T( 0.5)), T(boost::math::ellint_d(v_t(0.5), eve::pio_4(as<v_t>()))), 1.5);
  TTS_ULP_EQUAL( eve::ellint_d(eve::pio_4(as<T>()), T( 0.9)), T(boost::math::ellint_d(v_t(0.9), eve::pio_4(as<v_t>()))), 4.0);
  TTS_ULP_EQUAL( eve::ellint_d(3*eve::pio_4(as<T>()), T( 0.)),  T(boost::math::ellint_d(v_t(0)  , 3*eve::pio_4(as<v_t>()))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_d(3*eve::pio_4(as<T>()), T( 0.5)), T(boost::math::ellint_d(v_t(0.5), 3*eve::pio_4(as<v_t>()))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_d(3*eve::pio_4(as<T>()), T( 0.9)), T(boost::math::ellint_d(v_t(0.9), 3*eve::pio_4(as<v_t>()))), 1.0);
  TTS_ULP_EQUAL( eve::ellint_d(T(100), T( 0.)),  T(boost::math::ellint_d(v_t(0)  , v_t(100))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_d(T(100), T( 0.5)), T(boost::math::ellint_d(v_t(0.5), v_t(100))), 0.5);
  TTS_ULP_EQUAL( eve::ellint_d(T(100), T( 0.9)), T(boost::math::ellint_d(v_t(0.9), v_t(100))), 2.0);
  TTS_ULP_EQUAL( eve::ellint_d(T(1.5), T(1)),    T(boost::math::ellint_d(v_t(1)  , v_t(1.5))), 7.0);
}
