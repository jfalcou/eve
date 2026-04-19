/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of cumtrapz", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::cumtrapz(T(), T(), T(), T()), (kumi::tuple<T, T, T, T>));
  TTS_EXPR_IS(eve::cumtrapz(v_t(), v_t(), v_t(), v_t()), (kumi::tuple<v_t, v_t, v_t, v_t>));
  TTS_EXPR_IS(eve::cumtrapz(v_t(), T()  , v_t(), v_t()), (kumi::tuple<T, T, T, T>));
};

//==================================================================================================
// cumtrapz tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of cumtrapz on all types full range",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::cumtrapz;
  using eve::trapz;
  auto d = cumtrapz((a0), (a1), (a2), (a3));
  TTS_ULP_EQUAL(get<0>(d), eve::zero(eve::as(a0)), 1.5);
  TTS_ULP_EQUAL(get<1>(d), trapz(a0, a1), 1.5);
  TTS_ULP_EQUAL(get<2>(d), trapz(a0, a1, a2), 1.5);
  TTS_ULP_EQUAL(get<3>(d), trapz(a0, a1, a2, a3), 32.0);
};

TTS_CASE_WITH("Check behavior of cumtrapz on all types full range",
              eve::test::scalar::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::cumtrapz;
  using eve::trapz;
  auto d = cumtrapz((a0), (a1), (a2), (a3));
  TTS_ULP_EQUAL(get<0>(d), eve::zero(eve::as(a0)), 1.5);
  TTS_ULP_EQUAL(get<1>(d), trapz(a0, a1), 1.5);
  TTS_ULP_EQUAL(get<2>(d), trapz(a0, a1, a2), 1.5);
  TTS_ULP_EQUAL(get<3>(d), trapz(a0, a1, a2, a3), 1.5);
};
