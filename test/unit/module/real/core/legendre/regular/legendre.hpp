//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <boost/math/special_functions/legendre.hpp>
#include <eve/function/legendre.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::legendre return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::legendre(0, T(0)), T);
}

TTS_CASE_TPL("Check eve::legendre behavior", EVE_TYPE)
{

  auto eve__legendre =  [](auto n, auto x) { return eve::legendre(n, x); };
  auto boost_legendre =  [](auto n, auto x) { return boost::math::legendre_p(n, x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__legendre(2u, eve::minf(eve::as<T>())), eve::inf(eve::as<T>()), 5.0);
    TTS_ULP_EQUAL(eve__legendre(2u, eve::inf(eve::as<T>())), eve::inf(eve::as<T>()), 5.0);
    TTS_ULP_EQUAL(eve__legendre(3u, eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 5.0);
    TTS_ULP_EQUAL(eve__legendre(3u, eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 5.0);
    TTS_ULP_EQUAL(eve__legendre(3u, eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 5.0);
  }

  using i_t = eve::detail::as_integer_t<T,unsigned>;
  for(unsigned int i=0; i < 5; ++i)
  {
    for(double v = -1.0; v <= 1.0f; v+= 0.1)
    {
      TTS_ULP_EQUAL(eve__legendre(i, T(v)), T(boost_legendre(i, v)), 5);
      TTS_ULP_EQUAL(eve__legendre(i_t(i), T(v)), T(boost_legendre(i, v)), 5);
    }
  }
}
