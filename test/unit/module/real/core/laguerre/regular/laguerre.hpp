//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/laguerre.hpp>
#include <eve/function/laguerre.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::laguerre return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::laguerre(0, T(0)), T);
}

TTS_CASE_TPL("Check eve::laguerre behavior", EVE_TYPE)
{

  auto eve__laguerre =  [](auto n, auto x) { return eve::laguerre(n, x); };
  auto boost_laguerre =  [](auto n, auto x) { return boost::math::laguerre(n, x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__laguerre(2u, eve::minf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__laguerre(2u, eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__laguerre(3u, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__laguerre(3u, eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__laguerre(3u, eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  for(unsigned int i=0; i < 5; ++i)
  {
    TTS_ULP_EQUAL(eve__laguerre(i, T(10)), T(boost_laguerre(i, 10)), 1);
    TTS_ULP_EQUAL(eve__laguerre(i, T(5)), T(boost_laguerre(i, 5)), 1);
    TTS_ULP_EQUAL(eve__laguerre(i, T(2)), T(boost_laguerre(i, 2)), 1);
    TTS_ULP_EQUAL(eve__laguerre(i, T(1)), T(boost_laguerre(i, 1)), 1);
    TTS_ULP_EQUAL(eve__laguerre(i, T(0)), T(boost_laguerre(i, 0)), 1);
  }
}
