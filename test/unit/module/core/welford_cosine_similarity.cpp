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
// TTS_CASE_TPL("Check return types of welford_cosine_similarity", eve::test::simd::ieee_reals)
// <typename T>(tts::type<T>)
// {
//   using v_t = eve::element_type_t<T>;
//   using v3_t =      vec3<v_t>;
//   using wv3_t = eve::wide<v3_t>;
// //  using f_t =   eve::wide<v_t, eve::fixed<wv3_t::size()>>;
//   using r_t = eve::detail::welford_cosine_similarity_result<T>;
//   using vr_t =eve::detail::welford_cosine_similarity_result<v_t>;
//   TTS_EXPR_IS(eve::welford_cosine_similarity(wv3_t(), wv3_t()), r_t);
//   TTS_EXPR_IS(eve::welford_cosine_similarity(wv3_t(), v3_t()),  r_t);
//   TTS_EXPR_IS(eve::welford_cosine_similarity( v3_t(),wv3_t()),  r_t);
//   TTS_EXPR_IS(eve::welford_cosine_similarity(v3_t(),  v3_t()),  vr_t);
// };

//==================================================================================================
//== welford_cosine_similarity tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of welford_cosine_similarity(wide)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using  v3_t =  vec3<v_t>;
  v3_t a(1.0, 2.0, 3.0);
  v3_t b(-3.0, -4.0, -6.0);

  TTS_ULP_EQUAL(eve::welford_cosine_similarity(a, b).cosine_similarity, v_t(-0.9923595707022745), 0.5);

  std::cout << std::setprecision(16);
  using wv3_t =  eve::wide<v3_t, eve::fixed<4>>;
  using  f4_t =  eve::wide<v_t, eve::fixed<4>>;

  auto wa = wv3_t(a, a, b, b);
  auto wb = wv3_t(b, a, a, b);

  f4_t cwu{-0.9923595707022745, 1.0, -0.9923595707022745, 1.0};
  TTS_ULP_EQUAL(eve::welford_cosine_similarity(wa, wb).cosine_similarity, cwu, 0.5);
  f4_t cw{-0.9923595707022745, 1, 1, -0.9923595707022745};
  TTS_ULP_EQUAL(eve::welford_cosine_similarity(a, wb).cosine_similarity, cw, 0.5);
  f4_t cw3{-0.9923595707022745, -0.9923595707022745, 1.0, 1.0};
  TTS_ULP_EQUAL(eve::welford_cosine_similarity(wa, b).cosine_similarity, cw3, 0.5);

  auto cswab = eve::welford_cosine_similarity(wa, wb);
  std::cout << "scalarized" << eve::welford_cosine_similarity(cswab) << std::endl; ;

 {
    // incremental computation versus global computation
    auto constexpr N = 11;
    std::array<v_t, N> aa, bb;

    for(int i=0; i < N; ++i)
    {
      aa[i] = cos(i+1);
      bb[i] = cos(i+1)+1/v_t(i+1);
    }

//    std::cout << eve::welford_cosine_similarity(aa, bb) << std::endl;

    auto cc = eve::welford_cosine_similarity(kumi::make_tuple(aa[0]), kumi::make_tuple(bb[0]));
    for(int i=1; i < N; ++i)
    {
      auto dd = eve::welford_cosine_similarity(kumi::make_tuple(aa[i]), kumi::make_tuple(bb[i]));
//      std::cout << dd << std::endl;
      cc = eve::welford_cosine_similarity(cc, dd);
//      std::cout << cc.cosine_similarity << std::endl;
    }
    TTS_ULP_EQUAL(cc.cosine_similarity, eve::welford_cosine_similarity(aa, bb).cosine_similarity, 0.5);

    auto s = eve::welford_cosine_similarity(aa, bb);
    std::cout <<   eve::detail::is_welford_cosine_similarity_result_v<decltype(s)> << std::endl;

 //   std::cout << eve::welford_cosine_similarity(s, s) << std::endl;
//    std::cout << eve::welford_cosine_similarity(eve::welford_cosine_similarity(aa, bb), eve::welford_cosine_similarity(aa, bb)) << std::endl;
 }
};
