//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
  using i_t = eve::as_integer_t<T,unsigned>;
  for(unsigned int i=0; i < 5; ++i)
  {
    for(double v = -1.0; v <= 1.0f; v+= 0.1)
    {
      TTS_ULP_EQUAL(eve__legendre(i, T(v)), T(boost_legendre(i, v)), 15);
      TTS_ULP_EQUAL(eve__legendre(i_t(i), T(v)), T(boost_legendre(i, v)), 15);
    }
  }
}

