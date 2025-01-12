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
TTS_CASE_TPL("Check return types of ellint_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::ellint_2(T()), T);
  TTS_EXPR_IS(eve::ellint_2(v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_2(T(), T()), T);
  TTS_EXPR_IS(eve::ellint_2(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::ellint_2(T(), v_t()), T);
  TTS_EXPR_IS(eve::ellint_2(v_t(), T()), T);
};


//==================================================================================================
// ellint_1  tests
//==================================================================================================
TTS_CASE_TPL ( "Check ellint_2 over real"
             ,  eve::test::scalar::ieee_reals
             )
  <typename T>(tts::type<T>)
{
  using a_t  = std::array<T, 7 >;
  a_t phi= {0.0, 2.617993877991494e-01, 5.235987755982988e-01, 7.853981633974483e-01, 1.047197551196598e+00, 1.308996938995747e+00, 1.570796326794897e+00};
  a_t m=   {0.0, 1.428571428571428e-01, 2.857142857142857e-01, 4.285714285714285e-01, 5.714285714285714e-01, 7.142857142857143e-01, 8.571428571428572e-01};
  a_t re = {0.0, 2.613773716952197e-01, 5.170559866628908e-01, 7.537078152062719e-01, 9.521106010830449e-01, 1.089312605410849e+00, 1.138126250039161e+00};
  for(int i=0; i <= 6; ++i)
  {
    T z(phi[i]);
    auto e = eve::ellint_2(z, eve::sqrt(m[i]));
    TTS_ULP_EQUAL(e, re[i], 4.0);
  }
};


//==================================================================================================
// Tests for masked ellint_2
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::ellint_2)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 1.0),
                            tts::randoms(0, eve::pio_2),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::ellint_2[mask](a0),
            eve::if_else(mask, eve::ellint_2(a0), a0));
  TTS_IEEE_EQUAL(eve::ellint_2[mask](a0, a1),
            eve::if_else(mask, eve::ellint_2(a0, a1), a0));
};
