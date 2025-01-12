//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/elliptic.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ellint_fe", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::ellint_fe(T()), decltype(eve::zip(T(), T())));
  TTS_EXPR_IS(eve::ellint_fe(v_t()), decltype(eve::zip(v_t(), v_t())));
  TTS_EXPR_IS(eve::ellint_fe(T(), T()), decltype(eve::zip(T(), T())));
  TTS_EXPR_IS(eve::ellint_fe(v_t(), v_t()), decltype(eve::zip(v_t(), v_t())));
  TTS_EXPR_IS(eve::ellint_fe(T(), v_t()), decltype(eve::zip(T(), T())));
  TTS_EXPR_IS(eve::ellint_fe(v_t(), T()), decltype(eve::zip(T(), T())));
};


//==================================================================================================
// ellint_1  tests
//==================================================================================================
TTS_CASE_TPL ( "Check ellint_fe over real"
             ,  eve::test::scalar::ieee_reals
             )
  <typename T>(tts::type<T>)
{
  using a_t  = std::array<T, 7 >;
  a_t phi= {0.0, 2.617993877991494e-01, 5.235987755982988e-01, 7.853981633974483e-01, 1.047197551196598e+00, 1.308996938995747e+00, 1.570796326794897e+00};
  a_t m=   {0.0, 1.428571428571428e-01, 2.857142857142857e-01, 4.285714285714285e-01, 5.714285714285714e-01, 7.142857142857143e-01, 8.571428571428572e-01};
  a_t re = {0.0, 2.613773716952197e-01, 5.170559866628908e-01, 7.537078152062719e-01, 9.521106010830449e-01, 1.089312605410849e+00, 1.138126250039161e+00};
  a_t rf = {0.000000000000000e+00, 2.622226268962044e-01, 5.302901742393376e-01, 8.195141278162292e-01, 1.160270380410925e+00, 1.620041013035748e+00, 2.411575527618959e+00};
  for(int i=0; i <= 6; ++i)
  {
    T z(phi[i]);
    auto [f, e] = eve::ellint_fe(z, eve::sqrt(m[i]));
    auto [mf, me] =  eve::ellint_fe(-z, eve::sqrt(m[i]));
    TTS_ULP_EQUAL(e, re[i], 6.0);
    TTS_ULP_EQUAL(f, rf[i], 6.0);
    TTS_ULP_EQUAL(me, -re[i], 6.0);
    TTS_ULP_EQUAL(mf, -rf[i], 6.0);
  }
};
