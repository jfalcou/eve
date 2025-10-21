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
TTS_CASE_WITH("Check behavior of welford_covariance(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T const&,  T const& , T const& )
{
  using v_t = eve::element_type_t<T>;
  using  v3_t =  vec3<v_t>;
  v3_t a(1.0, 2.0, 3.0);
  v3_t b(-3.0, -4.0, -6.0);
  TTS_ULP_EQUAL(eve::welford_covariance[eve::unbiased](a, b).covariance, v_t(-1.5), 0.5);
  TTS_ULP_EQUAL(eve::welford_covariance(a, b).covariance, v_t(-1), 0.5);

//   using wv3_t =  eve::wide<v3_t, eve::fixed<4>>;
//   using  f4_t =  eve::wide<v_t, eve::fixed<4>>;
//   auto wa = wv3_t(a, a, b, b);
//   auto wb = wv3_t(b, a, a, b);
//   f4_t cwu{-1.5, 1, -1.5, 7.0/3.0};
//   TTS_ULP_EQUAL(eve::welford_covariance[eve::unbiased](wa, wb).covariance, cwu, 1.0);
//   f4_t cw{-1, 2.0/3.0, -1, 14.0/9.0};
//   TTS_ULP_EQUAL(eve::welford_covariance(wa, wb).covariance, cw, 1.0);
//   f4_t cw3{-1, -1, 14.0/9.0, 14.0/9.0};
//   TTS_ULP_EQUAL(eve::welford_covariance(wa, b).covariance, cw3, 1.0);

//   auto wcab = eve::welford_covariance[eve::unbiased](wa, wb);
//   auto wcaa = eve::welford_covariance[eve::unbiased](wa, wa);
//   auto wcbb = eve::welford_covariance[eve::unbiased](wb, wb);
//   auto r  = eve::welford_covariance(wcab, wcaa, wcbb);
//   std::cout << r << std::endl;
//   std::cout << eve::welford_covariance(eve::welford_covariance(wcab, wcaa), wcbb)  << std::endl;

//   std::cout << eve::welford_covariance(r) << std::endl;

  auto cab = eve::welford_covariance[eve::unbiased](a, b);
  std::cout << eve::welford_covariance[eve::unbiased](cab) << std::endl;
//   auto caa = eve::welford_covariance[eve::unbiased](a, a);
//   auto cbb = eve::welford_covariance[eve::unbiased](b, b);
//   std::cout << tts::typename_<decltype(cab)> << std::endl;
//   std::cout << eve::welford_covariance(cab, caa, cbb) << std::endl;
//   std::cout << eve::welford_covariance(eve::welford_covariance(cab, caa), cbb)  << std::endl;

};
