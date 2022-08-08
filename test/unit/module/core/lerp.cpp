/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of lerp", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::lerp(T(), T(), T()), T);
  TTS_EXPR_IS(eve::lerp(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::lerp(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::lerp(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::lerp(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::lerp(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::lerp(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// lerp tests
//==================================================================================================
auto mini = tts::constant([](auto tgt) { return -eve::sqrtvalmax(tgt); });

TTS_CASE_WITH("Check behavior of lerp on ieee floating",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, eve::sqrtvalmax),
                            tts::randoms(mini, eve::sqrtvalmax),
                            tts::randoms(0.0, 1.0)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::lerp;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::raw(lerp)((a0), (a1), (a2)),
                map([&](auto e, auto f, auto g) -> v_t { return std::lerp(e, f, g); }, a0, a1, a2),
                8);
  TTS_ULP_EQUAL(lerp((a0), (a1), (a2)),
                map([&](auto e, auto f, auto g) -> v_t { return std::lerp(e, f, g); }, a0, a1, a2),
                8);
  TTS_ULP_EQUAL(eve::pedantic(lerp)((a0), (a1), (a2)),
                map([&](auto e, auto f, auto g) -> v_t { return std::lerp(e, f, g); }, a0, a1, a2),
                8);
  TTS_ULP_EQUAL(eve::numeric(lerp)((a0), (a1), (a2)),
                map([&](auto e, auto f, auto g) -> v_t { return std::lerp(e, f, g); }, a0, a1, a2),
                8);
};
