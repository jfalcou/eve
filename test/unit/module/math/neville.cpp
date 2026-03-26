/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of neville", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::neville(T(), T(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::neville(T(), v_t(), v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::neville(v_t(), T(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::neville(T(), T(), v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::neville(v_t(), v_t(), v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::neville(v_t(), T(), v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::neville(v_t(), v_t(), v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// neville tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of neville on all types full range",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1, 10),
                            tts::randoms(1, 10),
                            tts::randoms(1, 10),
                            tts::randoms(-10, 10)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& x)
{
  using eve::abs;
  using eve::neville;
  using eve::horner;
  auto y0 = horner[eve::kahan](a0, 1.0, 2.0, 3.0);
  auto y1 = horner[eve::kahan](a1, 1.0, 2.0, 3.0);
  auto y2 = horner[eve::kahan](a2, 1.0, 2.0, 3.0);

  TTS_ULP_EQUAL(neville[eve::pedantic](x, a0, a1, a2, y0, y1, y2), eve::horner[eve::kahan](x, 1.0, 2.0, 3.0 ),3500.0);

};
