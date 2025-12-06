//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include "../../../vec3.hpp"

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of covariance", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using v3_t =      vec3<v_t>;
  using wv3_t = eve::wide<v3_t>;
  using r_t =   eve::wide<v_t, eve::fixed<wv3_t::size()>>;
  TTS_EXPR_IS(eve::covariance(wv3_t(), wv3_t()), r_t);
  TTS_EXPR_IS(eve::covariance(wv3_t(), v3_t()),  r_t);
  TTS_EXPR_IS(eve::covariance( v3_t(),wv3_t()),  r_t);
  TTS_EXPR_IS(eve::covariance(v3_t(),  v3_t()),  v_t);
};

//==================================================================================================
//== covariance tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of covariance(wide)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T const&,  T const& , T const& )
{
  using v_t = eve::element_type_t<T>;
  using  v3_t =  vec3<v_t>;
  v3_t a(1, 2, 3);
  v3_t b(-3, -4, -6);
  TTS_ULP_EQUAL(eve::covariance[eve::unbiased](a, b), -1.5, 0.5);
  TTS_ULP_EQUAL(eve::covariance(a, b), -1, 0.5);
  ;
  using wv3_t =  eve::wide<v3_t, eve::fixed<4>>;
  using  f4_t =  eve::wide<v_t, eve::fixed<4>>;
  TTS_ULP_EQUAL(eve::covariance[eve::unbiased](a, b), -1.5, 0.5);
  TTS_ULP_EQUAL(eve::covariance(a, b), -1, 0.5);
  auto wa = wv3_t(a, a, b, b);
  auto wb = wv3_t(b, a, a, b);
  f4_t cwu{static_cast<v_t>(-1.5), static_cast<v_t>(1), static_cast<v_t>(-1.5), static_cast<v_t>(7.0/3.0)};
  TTS_ULP_EQUAL(eve::covariance[eve::unbiased](wa, wb), cwu, 0.5);
  f4_t cw{static_cast<v_t>(-1), static_cast<v_t>(2.0/3.0), static_cast<v_t>(-1), static_cast<v_t>(14.0/9.0)};
  TTS_ULP_EQUAL(eve::covariance(wa, wb), cw, 0.5);
  f4_t cw3{static_cast<v_t>(-1), static_cast<v_t>(-1), static_cast<v_t>(14.0/9.0), static_cast<v_t>(14.0/9.0)};
  TTS_ULP_EQUAL(eve::covariance(wa, b), cw3, 0.5);
};
