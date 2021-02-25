//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ellint_3.hpp>
#include <boost/math/special_functions/ellint_3.hpp>
#include <boost/math/special_functions/ellint_1.hpp>
#include <eve/wide.hpp>


TTS_CASE_TPL("Check eve::ellint_3 behavior", EVE_TYPE)
{
  auto boost_el3 = [](auto n,  auto phi,  auto k){return boost::math::ellint_3(k, n, phi);};

  using elt_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::ellint_3(T(0.4), T(0), T(0.2)),       T(boost_el3(elt_t(0.4), elt_t(0), elt_t(0.2) )),      1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(1.0), T(0.25), T(0.5)),    T(boost_el3(elt_t(1),   elt_t(0.25), elt_t(0.5) )),   1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0.0), T(0.25), T(0.5)),    T(boost_el3(elt_t(0),   elt_t(0.25), elt_t(0.5) )),   1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0.3), T(0.25), T(0)  ),    T(boost_el3(elt_t(0.3), elt_t(0.25), elt_t(0)   )),   1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(1.2), T(0.25), T(0.25)),   T(boost_el3(elt_t(1.2), elt_t(0.25), elt_t(0.25) )),  1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0),   T(1.5), T(1)),       T(boost_el3(elt_t(0), elt_t(1.5), elt_t(1) )),      1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0),   T(2), T(1)),       T(eve::inf(eve::as<T>())),      1.0);
}

TTS_CASE_TPL("Check eve::ellint_3 behavior", EVE_TYPE)
{
  auto boost_el3 = [](auto n, auto k){return boost::math::ellint_3(k, n);};

  using elt_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::ellint_3(T(0.4), T(0.2)),    T(boost_el3(elt_t(0.4),  elt_t(0.2) )),   1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0.9), T(0.5)),    T(boost_el3(elt_t(0.9),  elt_t(0.5) )),   1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0.0), T(0.5)),    T(boost_el3(elt_t(0),    elt_t(0.5) )),   1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0.3), T(0)  ),    T(boost_el3(elt_t(0.3),  elt_t(0)   )),   1.0);
  TTS_ULP_EQUAL(eve::ellint_3(T(0.8), T(0.25)),   T(boost_el3(elt_t(0.8),  elt_t(0.25) )),  1.0);
}
