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
TTS_CASE_TPL("Check return types of betainc", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::betainc(T(), T(), T()), T);
  TTS_EXPR_IS(eve::betainc(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::betainc(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::betainc(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::betainc(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::betainc(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::betainc(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::betainc(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// betainc  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of betainc on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::betainc;
  TTS_EQUAL(eve::betainc(T(0), T(0), T(0)), T(0));
  TTS_EQUAL(eve::betainc(T(0), T(0), T(7)), T(0));
  TTS_ULP_EQUAL(eve::betainc(T(0.5), T(0.5), T(0.5)), T(0.5), 15);
  TTS_ULP_EQUAL(eve::betainc(T(0.2), T(0.3), T(2)), T(7.651219897728122e-01), 30);
};


//==================================================================================================
// Tests for masked betainc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::betainc)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         T const& a2,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::betainc[mask](a0, a1, a2),
            eve::if_else(mask, eve::betainc(a0, a1, a2), a0));
};
