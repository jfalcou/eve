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
  using i_t = eve::as_integer_t<T,unsigned>;
  using elt_t = eve::element_type_t<T>;
  for(unsigned int i=0; i < 5; ++i)
  {
    for(elt_t v1 = -10; v1 <= 10; v1+=1)
    {
      auto v = v1/elt_t(10);
      TTS_ULP_EQUAL(eve__laguerre(i, T(v)), T(boost_laguerre(i, v)), 15);
      TTS_ULP_EQUAL(eve__laguerre(i_t(i), T(v)), T(boost_laguerre(i, v)), 15);
    }
  }
}
