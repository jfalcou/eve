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
TTS_CASE_TPL("Check return types of logspace_add", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::logspace_add(T(), T()), T);
  TTS_EXPR_IS(eve::logspace_add(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::logspace_add(T(), v_t()), T);
  TTS_EXPR_IS(eve::logspace_add(v_t(), T()), T);
  TTS_EXPR_IS(eve::logspace_add(T(), T(), T()), T);
  TTS_EXPR_IS(eve::logspace_add(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::logspace_add(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::logspace_add(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::logspace_add(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::logspace_add(v_t(), T(), v_t()), T);

  TTS_EXPR_IS(eve::logspace_add(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// logspace_add  tests
//==================================================================================================
auto maxi = tts::constant([]<typename T>(eve::as<T> const& tgt) { return eve::valmax(tgt) / 3; });

TTS_CASE_WITH("Check behavior of logspace_add on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, maxi),
                            tts::randoms(0.0, maxi),
                            tts::randoms(0.5, 2.0),
                            tts::randoms(0.5, 2.0),
                            tts::randoms(0.0, maxi),
                            tts::randoms(0.5, 2.0)))
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4, T const& a5)
{
  using eve::detail::map;

  auto la0 = eve::log(a0);
  auto la1 = eve::log(a1);
  auto la2 = eve::log(a2);
  auto la3 = eve::log(a3);
  TTS_ULP_EQUAL(eve::logspace_add(la0, la1), eve::log(a0 + a1), 20);
  TTS_ULP_EQUAL(eve::logspace_add(la2, la3), eve::log(a2 + a3), 20);

  auto la4 = eve::log(a4);
  auto la5 = eve::log(a5);
  TTS_ULP_EQUAL(eve::logspace_add(la0, la1, la4), eve::log(a0 + a1 + a4), 20);
  TTS_ULP_EQUAL(eve::logspace_add(la2, la3, la5), eve::log(a2 + a3 + a5), 20);
  TTS_ULP_EQUAL(eve::logspace_add(kumi::tuple{la0, la1, la4}), eve::log(a0 + a1 + a4), 20);
  TTS_ULP_EQUAL(eve::logspace_add(kumi::tuple{la2, la3, la5}), eve::log(a2 + a3 + a5), 20);
};


//==================================================================================================
// Tests for masked logspace_add
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::logspace_add)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::logspace_add[mask](a0, a1),
            eve::if_else(mask, eve::logspace_add(a0, a1), a0));
};
