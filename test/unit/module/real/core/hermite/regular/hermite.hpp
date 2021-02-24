//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/hermite.hpp>
#include <eve/function/hermite.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::hermite return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::hermite(0, T(0)), T);
}

TTS_CASE_TPL("Check eve::hermite behavior", EVE_TYPE)
{

  auto eve__hermite =  [](auto n, auto x) { return eve::hermite(n, x); };
  auto boost_hermite =  [](auto n, auto x) { return boost::math::hermite(n, x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__hermite(2u, eve::minf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__hermite(2u, eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__hermite(3u, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__hermite(3u, eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__hermite(3u, eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  for(unsigned int i=0; i < 10; ++i)
  {
    TTS_ULP_EQUAL(eve__hermite(i, T(10)), T(boost_hermite(i, 10)), 1);
    TTS_ULP_EQUAL(eve__hermite(i, T(5)), T(boost_hermite(i, 5)), 1);
    TTS_ULP_EQUAL(eve__hermite(i, T(2)), T(boost_hermite(i, 2)), 1);
    TTS_ULP_EQUAL(eve__hermite(i, T(1)), T(boost_hermite(i, 1)), 1);
    TTS_ULP_EQUAL(eve__hermite(i, T(0)), T(boost_hermite(i, 0)), 1);
  }
}
