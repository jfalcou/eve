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

// Nodes at least one apart and x between them keep the Lagrange factors under 10: the error stays
// under 45 ULP over 200 000 draws, where close nodes or an x outside reach 10^8.
TTS_CASE_WITH("Check behavior of neville on all types full range",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(1, 3),
                            tts::randoms(4, 6),
                            tts::randoms(7, 10),
                            tts::randoms(1, 10)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& x)
{
  using eve::abs;
  using eve::neville;
  using eve::horner;
  auto y0 = horner[eve::kahan](a0, 1.0, 2.0, 3.0);
  auto y1 = horner[eve::kahan](a1, 1.0, 2.0, 3.0);
  auto y2 = horner[eve::kahan](a2, 1.0, 2.0, 3.0);

  TTS_ULP_EQUAL(neville[eve::pedantic](x, a0, a1, a2, y0, y1, y2), eve::horner[eve::kahan](x, 1.0, 2.0, 3.0 ), 128.0);

};
