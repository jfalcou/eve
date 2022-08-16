//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of atan2d", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::atan2d(T(), T()), T);
  TTS_EXPR_IS(eve::atan2d(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::atan2d(T(), v_t()), T);
  TTS_EXPR_IS(eve::atan2d(v_t(), T()), T);
};

//==================================================================================================
// atan2d  tests
//==================================================================================================
auto mini = tts::constant([](auto tgt) { return eve::next(eve::mindenormal(tgt)); });
auto maxi = tts::constant([](auto tgt) { return eve::valmax(tgt) / 2; });

TTS_CASE_WITH("Check behavior of atan2d on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(mini, maxi),
                            tts::randoms(mini, maxi),
                            tts::randoms(-1.0, 1.0),
                            tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::atan2d(a0, a1),
                map([](auto e, auto f) -> v_t { return eve::radindeg(std::atan2(e, f)); }, a0, a1),
                2);
  TTS_ULP_EQUAL(eve::atan2d(a2, a3),
                map([](auto e, auto f) -> v_t { return eve::radindeg(std::atan2(e, f)); }, a2, a3),
                2);
};
