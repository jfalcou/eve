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
TTS_CASE_TPL("Check return types of diff", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::diff(T(), T(), T(), T()), (kumi::tuple<T, T, T>));
  TTS_EXPR_IS(eve::diff(v_t(), v_t(), v_t(), v_t()), (kumi::tuple<v_t, v_t, v_t>));
  TTS_EXPR_IS(eve::diff(v_t(), T()  , v_t(), v_t()), (kumi::tuple<T, T, T>));
};

//==================================================================================================
// diff tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of diff on all types full range",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::diff;
  auto d = diff((a0), (a1), (a2), (a3));
  TTS_EQUAL(get<0>(d), a0-a1);
  TTS_EQUAL(get<1>(d), a1-a2);
  TTS_EQUAL(get<2>(d), a2-a3);
};
