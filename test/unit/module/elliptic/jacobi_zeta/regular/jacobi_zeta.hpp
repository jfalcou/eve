//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/jacobi_zeta.hpp>
#include <boost/math/special_functions/jacobi_zeta.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp>

#include <cmath>

TTS_CASE_TPL("Check eve::jacobi_zeta return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::jacobi_zeta(T(0), T(0)), T);
}


TTS_CASE_TPL("Check eve::jacobi_zeta behavior two parameter", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;
  if constexpr( eve::platform::supports_invalids )
  {
   TTS_IEEE_EQUAL(eve::jacobi_zeta(eve::pio_4(as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
   TTS_ULP_EQUAL(eve::jacobi_zeta(eve::pio_2(as<T>()), T(1)) , eve::zero(eve::as<T>()), 0.5);
   TTS_ULP_EQUAL(eve::jacobi_zeta(eve::pio_2(as<T>()), T(-1)), eve::zero(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL( eve::jacobi_zeta(eve::pio_2(as<T>()), T( 0.)),  eve::zero(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL( eve::jacobi_zeta(eve::pio_2(as<T>()), T( 0.5)), eve::zero(eve::as<T>()), 4);
  TTS_ULP_EQUAL( eve::jacobi_zeta(eve::pio_2(as<T>()), T( 0.9)), eve::zero(eve::as<T>()), 4.55);

  TTS_ULP_EQUAL( eve::jacobi_zeta(eve::pio_4(as<T>()), T( 0.)),  T(boost::math::jacobi_zeta(v_t(0)  , eve::pio_4(as<v_t>()))), 0.5);
  TTS_ULP_EQUAL( eve::jacobi_zeta(eve::pio_4(as<T>()), T( 0.5)), T(boost::math::jacobi_zeta(v_t(0.5), eve::pio_4(as<v_t>()))), 1.0);
  TTS_ULP_EQUAL( eve::jacobi_zeta(eve::pio_4(as<T>()), T( 0.9)), T(boost::math::jacobi_zeta(v_t(0.9), eve::pio_4(as<v_t>()))), 1.0);
  TTS_ULP_EQUAL( eve::jacobi_zeta(3*eve::pio_4(as<T>()), T( 0.)),  T(boost::math::jacobi_zeta(v_t(0)  , 3*eve::pio_4(as<v_t>()))), 0.5);
  TTS_ULP_EQUAL( eve::jacobi_zeta(T(100), T( 0.)),  T(boost::math::jacobi_zeta(v_t(0)  , v_t(100))), 0.5);
  TTS_ULP_EQUAL( eve::jacobi_zeta(T(1.5), T(1)),    T(boost::math::jacobi_zeta(v_t(1)  , v_t(1.5))), 1.0);

  {
    auto z1 = eve::jacobi_zeta(eve::pio_2(as<T>()), T(0.9));
    auto z2 = boost::math::jacobi_zeta(v_t(0.9), eve::pio_2(as<v_t>()));
    std::cout <<  z1 << std::endl;
    std::cout <<  z2 << std::endl;
  }

  TTS_ULP_EQUAL( eve::jacobi_zeta(3*eve::pio_4(as<T>()), T( 0.5)), T(boost::math::jacobi_zeta(v_t(0.5), 3*eve::pio_4(as<v_t>()))), 0.5);
  TTS_ULP_EQUAL( eve::jacobi_zeta(3*eve::pio_4(as<T>()), T( 0.9)), T(boost::math::jacobi_zeta(v_t(0.9), 3*eve::pio_4(as<v_t>()))), 0.5);
  TTS_ULP_EQUAL( eve::jacobi_zeta(T(100), T( 0.5)), T(boost::math::jacobi_zeta(v_t(0.5), v_t(100))), 1.0);
  TTS_ULP_EQUAL( eve::jacobi_zeta(T(100), T( 0.9)), T(boost::math::jacobi_zeta(v_t(0.9), v_t(100))), 1.0);
}
