//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/detail/vec3.hpp>
//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of welford_covariance", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using v3_t = vec3<v_t>;
  using wv3_t = eve::wide<v3_t>;
  using wr_t = eve::detail::welford_covariance_result<kumi::apply_traits_t<eve::common_value, wv3_t>>;
  using vr_t = eve::detail::welford_covariance_result<kumi::apply_traits_t<eve::common_value, v3_t>>;
  TTS_EXPR_IS(eve::welford_covariance(wv3_t(), wv3_t()), wr_t);
  TTS_EXPR_IS(eve::welford_covariance(wv3_t(), v3_t()),  wr_t);
  TTS_EXPR_IS(eve::welford_covariance( v3_t(),wv3_t()),  wr_t);
  TTS_EXPR_IS(eve::welford_covariance(v3_t(),  v3_t()),  vr_t);
};

//==================================================================================================
//== welford_covariance tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of welford_covariance", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using  v3_t =  vec3<v_t>;
  v3_t a(1.0, 2.0, 3.0);
  v3_t b(-3.0, -4.0, -6.0);
  TTS_ULP_EQUAL(eve::welford_covariance[eve::unbiased](a, b).covariance, v_t(-1.5), 0.5);
  TTS_ULP_EQUAL(eve::welford_covariance(a, b).covariance, v_t(-1), 0.5);

  using wv3_t =  eve::wide<v3_t, eve::fixed<4>>;
  using f4_t =  eve::wide<v_t, eve::fixed<4>>;
  auto wa = wv3_t(a, a, b, b);
  auto wb = wv3_t(b, a, a, b);
  f4_t cwu{-1.5, 1, -1.5, 7.0/3.0};
  TTS_ULP_EQUAL(eve::welford_covariance[eve::unbiased](wa, wb).covariance, cwu, 1.0);
  f4_t cw{-1, 2.0/3.0, -1, 14.0/9.0};
  TTS_ULP_EQUAL(eve::welford_covariance(wa, wb).covariance, cw, 1.0);
  f4_t cw3{-1, -1, 14.0/9.0, 14.0/9.0};
  TTS_ULP_EQUAL(eve::welford_covariance(wa, b).covariance, cw3, 1.0);

  auto t1 = kumi::generate<11>([](auto p){return float(p); });
  auto t2 = kumi::generate<11>([](auto p){return float(p*p); });
  TTS_ULP_EQUAL(eve::welford_covariance(t1, t2).covariance, 100.0f, 1.0);

  using w_t = eve::wide<float, eve::fixed<4>>;
  auto wt1 = kumi::generate<11>([](auto p){return w_t([p](auto q, auto){return float(p+q); }); });
  auto wt2 = kumi::generate<11>([](auto p){return w_t([p](auto q, auto){return p*p/float((q+1)); }); });
  auto z = eve::welford_covariance(wt1, wt2);
  TTS_ULP_EQUAL(z.covariance, w_t(100.0f, 50.0f, 100/3.0f, 25.0f), 1.0);
  TTS_ULP_EQUAL(eve::welford_covariance(z).covariance, 41.5104179382324f, 1.0); //scalarization
};
