//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ellint_rc.hpp>

#include <boost/math/special_functions/ellint_rc.hpp>
#include <eve/wide.hpp>


TTS_CASE_TPL("Check eve::ellint_rc behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::ellint_rc(T(0.2), T(0.4)),  T(boost::math::ellint_rc(elt_t(0.2), elt_t(0.4))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(1.5), T(1)),T(boost::math::ellint_rc(elt_t(1.5), elt_t(1))), 1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(0), T(5)),  T(boost::math::ellint_rc(elt_t(0), elt_t(5))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(2), T(5)),  T(boost::math::ellint_rc(elt_t(2), elt_t(5))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(2), T(2)),  T(boost::math::ellint_rc(elt_t(2), elt_t(2))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(2), T(0.1)),  T(boost::math::ellint_rc(elt_t(2), elt_t(0.1))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(1.0e38), T(0.1)),  T(boost::math::ellint_rc(elt_t(1.0e38), elt_t(0.1))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(1.0), T(1.0e38)),  T(boost::math::ellint_rc(elt_t(1.0),elt_t(1.0e38))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rc(T(1.0e38), T(1.0e38)),  T(boost::math::ellint_rc(elt_t(1.0e38),elt_t(1.0e38))),   1.0);
}

