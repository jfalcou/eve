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
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return abs(a) + abs(b) + abs(c); };
  TTS_ULP_EQUAL(manhattan((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(manhattan[eve::pedantic]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(manhattan(kumi::tuple{a0, a1, a2}), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(manhattan[eve::pedantic](kumi::tuple{a0, a1, a2}), tts::map(m, a0, a1, a2), 2);
  auto t = [](auto p){ return (p == T::size()-1) ? v_t(100) : v_t(5); };
  constexpr auto s = 3*T::size()/2;
  auto tup = kumi::generate<s>(t);
  TTS_ULP_EQUAL(manhattan(tup), v_t(100)+v_t(5)*(3*T::size()/2-1), 0.5);
};


//==================================================================================================
// Tests for masked manhattan
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::manhattan)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
  <typename T, typename M>(T const& a0,
                           T const& a1,
                           M const& mask)
{
  TTS_IEEE_EQUAL(eve::manhattan[mask](a0, a1),
                 eve::if_else(mask, eve::manhattan(a0, a1), a0));
};

TTS_CASE_WITH("Check behavior of manhattan kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::manhattan;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(manhattan[kahan](a0, a1, a2), eve::downgrade(manhattan[widen](a0, a1, a2)), 0.5);

};
