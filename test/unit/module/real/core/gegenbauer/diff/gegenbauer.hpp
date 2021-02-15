//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/diff_div.hpp>
#include <eve/function/diff/gegenbauer.hpp>
#include <boost/math/special_functions/gegenbauer.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(gegenbauer) return type", EVE_TYPE)
{
    TTS_EXPR_IS(eve::diff(eve::gegenbauer)((unsigned int)(0), T(), T()), T);
}

TTS_CASE_TPL("Check eve::diff(eve::gegenbauer) behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  elt_t l(-3.0/8.0);
  auto eve__gegenbauer =  [&l](unsigned n, auto x) { return eve::diff(eve::gegenbauer)(n, T(l), x); };
  auto boost_gegenbauer =  [&l](unsigned n, auto x) { return boost::math::gegenbauer_derivative(n, double(l), x, 1u); };

  for(unsigned int i=0; i < 10; ++i)
  {
    TTS_ULP_EQUAL(eve__gegenbauer(i, T(10)), T(boost_gegenbauer(i, 10.0)), 1);
    TTS_ULP_EQUAL(eve__gegenbauer(i, T(5)), T(boost_gegenbauer(i, 5.0)), 1);
    TTS_ULP_EQUAL(eve__gegenbauer(i, T(2)), T(boost_gegenbauer(i, 2.0)), 1);
    TTS_ULP_EQUAL(eve__gegenbauer(i, T(1)), T(boost_gegenbauer(i, 1.0)), 20);
    TTS_ULP_EQUAL(eve__gegenbauer(i, T(0)), T(boost_gegenbauer(i, 0.0)), 1);
  }
}
