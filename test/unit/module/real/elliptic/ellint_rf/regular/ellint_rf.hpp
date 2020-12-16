//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ellint_rf.hpp>
#include <boost/math/special_functions/ellint_rf.hpp>
#include <eve/wide.hpp>


TTS_CASE_TPL("Check eve::ellint_rf behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::ellint_rf(T(0.2), T(0.4), T(0)),  T(boost::math::ellint_rf(elt_t(0.2), elt_t(0.4), elt_t(0))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rf(T(1.5), T(1), T(7)),T(boost::math::ellint_rf(elt_t(1.5), elt_t(1), elt_t(7))), 1.0);
  TTS_ULP_EQUAL(eve::ellint_rf(T(2), T(0), T(7)),  T(boost::math::ellint_rf(elt_t(2), elt_t(0), elt_t(7))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rf(T(0), T(5), T(7)),  T(boost::math::ellint_rf(elt_t(0), elt_t(5), elt_t(7))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rf(T(2), T(5), T(7)),  T(boost::math::ellint_rf(elt_t(2), elt_t(5), elt_t(7))),   1.0);
                                                                        }
