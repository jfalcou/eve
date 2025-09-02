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
TTS_CASE_TPL("Check return types of dot", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::dot(T(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::dot(T(), v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::dot(v_t(), T(), T(), T()), T);
  TTS_EXPR_IS(eve::dot(T(), T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::dot(v_t(), v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::dot(v_t(), T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::dot(v_t(), v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// dot tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of dot on all types full range",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using eve::abs;
  using eve::dot;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c, auto d) -> v_t { return a*c+b*d; };
  TTS_ULP_EQUAL(dot((a0), (a1), (a2), (a3)), tts::map(m, a0, a1, a2, a3), 2);
  TTS_ULP_EQUAL(dot(kumi::tuple{a0, a1, a2, a3}), tts::map(m, a0, a1, a2, a3), 2);
  TTS_ULP_EQUAL(dot(kumi::tuple{a0, a1}, kumi::tuple{a2, a3}), tts::map(m, a0, a1, a2, a3), 2);
};


//==================================================================================================
// Tests for masked dot
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::dot)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::logicals(0, 3)))
  <typename T, typename M>(T const& a0,
                           T const& a1,
                           M const& mask)
{
  TTS_IEEE_EQUAL(eve::dot[mask](a0, a1, a0, a1),
                 eve::if_else(mask, eve::dot(a0, a1, a0, a1), a0));
};

TTS_CASE_WITH("Check behavior of dot kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
<typename T>(T const& a0, T const& a1,  T const&a2, T const& a3)
{
  using eve::dot;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(dot[kahan](a0, a1, a2, a3), eve::downgrade(dot[widen](a0, a1, a2, a3)), 0.5);

};
