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
TTS_CASE_TPL("Check return types of sum_of_squares", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::sum_of_squares(T(), T(), T()), T);
  TTS_EXPR_IS(eve::sum_of_squares(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sum_of_squares(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::sum_of_squares(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sum_of_squares(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::sum_of_squares(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::sum_of_squares(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// sum_of_squares tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of sum_of_squares on all types full range",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
  <typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::sqr;
  using eve::sum_of_squares;
  using v_t = eve::element_type_t<T>;
  auto m    = [](auto a, auto b, auto c) -> v_t { return sqr(a) + sqr(b) + sqr(c); };
  TTS_ULP_EQUAL(sum_of_squares((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(sum_of_squares[eve::pedantic]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(sum_of_squares(eve::zip((a0), (a1), (a2))), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(sum_of_squares[eve::pedantic](eve::zip((a0), (a1), (a2))), tts::map(m, a0, a1, a2), 2);
};


//==================================================================================================
// Tests for masked sum_of_squares
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::sum_of_squares)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
  <typename T, typename M>(T const& a0,
                           T const& a1,
                           M const& mask)
{
  TTS_IEEE_EQUAL(eve::sum_of_squares[mask](a0, a1),
                 eve::if_else(mask, eve::sum_of_squares(a0, a1), a0));
};

TTS_CASE_WITH("Check behavior of sum_of_squares kahan on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1,  T const&a2)
{
  using eve::sum_of_squares;
  using eve::widen;
  using eve::kahan;
  using eve::as;
  if constexpr(sizeof(eve::element_type_t<T>) < 8)
    TTS_ULP_EQUAL(sum_of_squares[kahan](a0, a1, a2), eve::downgrade(sum_of_squares[widen](a0, a1, a2)), 0.5);
};
