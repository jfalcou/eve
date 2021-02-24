//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ellint_rd.hpp>
#include <boost/math/special_functions/ellint_rd.hpp>
#include <eve/wide.hpp>


TTS_CASE_TPL("Check eve::ellint_rd behavior", EVE_TYPE)
{
  using elt_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::ellint_rd(T(0.2), T(0.4), T(0.1)),  T(boost::math::ellint_rd(elt_t(0.2), elt_t(0.4), elt_t(0.1))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rd(T(1.5), T(1), T(1.7)),T(boost::math::ellint_rd(elt_t(1.5), elt_t(1), elt_t(1.7))), 1.0);
  TTS_ULP_EQUAL(eve::ellint_rd(T(2), T(0), T(7)),  T(boost::math::ellint_rd(elt_t(2), elt_t(0), elt_t(7))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rd(T(0), T(5), T(3.4)),  T(boost::math::ellint_rd(elt_t(0), elt_t(5), elt_t(3.4))),   1.0);
  TTS_ULP_EQUAL(eve::ellint_rd(T(2), T(5), T(0.5)),  T(boost::math::ellint_rd(elt_t(2), elt_t(5), elt_t(0.5))),   1.0);
                                                                        }
