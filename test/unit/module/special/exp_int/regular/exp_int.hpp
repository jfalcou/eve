//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/expint.hpp>
#include <eve/function/exp_int.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::exp_int return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exp_int(T(0), T(0)), T);
  TTS_EXPR_IS(eve::exp_int(0, T(0)), T);
}

TTS_CASE_TPL("Check eve::exp_int behavior", EVE_TYPE)
{
  auto eve__exp_int   =  [](auto x, auto y) { return eve::exp_int(x, y); };
  auto boost__exp_int =  [](auto x, auto y) { return boost::math::expint(x, y); };

//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_IEEE_EQUAL(eve__exp_int(T(1), eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
//     TTS_IEEE_EQUAL(eve__exp_int(T(1), eve::inf(eve::as<T>()))   , T(0) );
//   }


  for(int i=1; i < 4 ; ++i)
  {
    TTS_ULP_EQUAL(eve__exp_int(T(i), T(0))  , eve::rec(T(i-1)), 0.5);
    TTS_ULP_EQUAL(eve__exp_int(T(i), T(0.5)), T(boost__exp_int(i, 0.5)), 2.0);
    TTS_ULP_EQUAL(eve__exp_int(T(i), T(1))  , T(boost__exp_int(i, 1.0)), 4.0);
    TTS_ULP_EQUAL(eve__exp_int(T(i), T(10)) , T(boost__exp_int(i, 10.0)), 0.5);
  }
  for(int i=1; i < 4 ; ++i)
  {
    TTS_ULP_EQUAL(eve__exp_int(i, T(0))  , eve::rec(T(i-1)), 0.5);
    TTS_ULP_EQUAL(eve__exp_int(i, T(0.5)), T(boost__exp_int(i, 0.5)), 2.0);
    TTS_ULP_EQUAL(eve__exp_int(i, T(1))  , T(boost__exp_int(i, 1.0)), 4.0);
    TTS_ULP_EQUAL(eve__exp_int(i, T(10)) , T(boost__exp_int(i, 10.0)), 0.5);
  }
  using elt_t =  eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve__exp_int(elt_t(2.0), elt_t(0.5)), (boost__exp_int(elt_t(2), elt_t(0.5))), 2.0);
  TTS_ULP_EQUAL(eve__exp_int(elt_t(6000), elt_t(0.5)), (boost__exp_int(elt_t(6000), elt_t(0.5))), 3.0);
}
