//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of trigamma", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::trigamma(T()), T);
  TTS_EXPR_IS(eve::trigamma(v_t()), v_t);
};

//==================================================================================================
// trigamma  tests
// //==================================================================================================
TTS_CASE_TPL("Check behavior of trigamma on wide", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::trigamma;
  using e_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(trigamma(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(trigamma(eve::inf(eve::as<T>())), eve::zero(eve::as<T>()));
    TTS_IEEE_EQUAL(trigamma(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }
  auto ulp = 300.0;

  TTS_ULP_EQUAL(trigamma(T(0.00001)), T(e_t(1.0000000001644909e10)), ulp);
  TTS_ULP_EQUAL(trigamma(T(0.125)), T(e_t(65.3881334449)), ulp*20);
  TTS_ULP_EQUAL(trigamma(T(0.5)), eve::pi2(eve::as<T>())/2, ulp);
  TTS_ULP_EQUAL(trigamma(T(1)), eve::pi2(eve::as<T>())/6, ulp);
  TTS_ULP_EQUAL(trigamma(T(1.5)),eve::pi2(eve::as<T>())/2-4, ulp);
  TTS_ULP_EQUAL(trigamma(T(2)), eve::pi2(eve::as<T>())/6-1, ulp);
  TTS_ULP_EQUAL(trigamma(T(8)), T(e_t(0.1331370146940314251345L)), 4*ulp);
  TTS_ULP_EQUAL(trigamma(T(500)), T(e_t(0.0020020013333322666L)), ulp);
//   //
//   // negative values:
//   //
  TTS_ULP_EQUAL(trigamma(T(-0.125)), T(e_t(66.00574095792491813882520)), ulp);
  TTS_ULP_EQUAL(trigamma(T(-10.125)), T(e_t(67.2998260174871030485)), ulp);
  TTS_ULP_EQUAL(trigamma(T(-11.125)), T(e_t(67.3079058053926705273)), ulp);
  TTS_ULP_EQUAL(trigamma(T(-1.5)), T(e_t(9.379246644989123753861689)), ulp);
};

TTS_CASE_WITH("Check behavior of trigamma on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.4, 4.0)))
  <typename T>(T const& a0) { TTS_ULP_EQUAL(eve::trigamma(a0), T(tts::map(eve::trigamma, a0)), 3); };


//==================================================================================================
// Tests for masked trigamma
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::trigamma)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.4, 4.0),
                            tts::logicals(0, 3)))
  <typename T, typename M>(T const& a0,
                           M const& mask)
{
  TTS_IEEE_EQUAL(eve::trigamma[mask](a0),
                 eve::if_else(mask, eve::trigamma(a0), a0));
};
