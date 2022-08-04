/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of manhattan", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::manhattan(T(), T(), T()), T);
  TTS_EXPR_IS(eve::manhattan(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::manhattan(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::manhattan(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::manhattan(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::manhattan(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::manhattan(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// manhattan tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of manhattan on all types full range",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::abs;
  using eve::manhattan;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return abs(a) + abs(b) + abs(c); };
  TTS_ULP_EQUAL(manhattan((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(manhattan)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
};
