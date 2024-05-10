//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of remainder", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::remainder;

  // regular
  TTS_EXPR_IS(remainder(T(), T()), T);
  TTS_EXPR_IS(remainder(T(), v_t()), T);
  TTS_EXPR_IS(remainder(v_t(), T()), T);
  TTS_EXPR_IS(remainder(v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(remainder[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(remainder[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(remainder[eve::logical<v_t>()](v_t(), v_t()), v_t);
};

//==================================================================================================
//==  remainder simd tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of remainder on wide",
              eve::test::simd::ieee_reals
              ,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
<typename T>(T a0, T a1)
{
  using eve::remainder;
  using eve::detail::map;

  auto thrs = std::same_as<eve::element_type_t<T>, float> ? 5e-4 : 5e-12;
  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_RELATIVE_EQUAL(remainder(a0, a1), map([](auto e, auto f) { return std::remainder(e, f); }, a0, a1), thrs);
};

TTS_CASE_WITH("Check behavior of fmod on wide corner cases",
              eve::test::simd::ieee_reals
              ,
              tts::generate(tts::randoms(1, 100),
                            tts::randoms(1, 100)))
<typename T>(T a0, T a1)
{
  using eve::remainder;
  using eve::detail::map;
  using eve::as;

  TTS_IEEE_EQUAL(remainder(T(0), a1), T(0));
  TTS_IEEE_EQUAL(remainder(-T(0), a1), T(0));
  TTS_IEEE_EQUAL(remainder(eve::inf(as<T>()), a1), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(remainder(eve::minf(as<T>()), a1), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(remainder(a0, eve::zero(as<T>())), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(remainder(a0, eve::mzero(as<T>())), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(remainder(a0, eve::inf(as<T>())), a0);
  TTS_IEEE_EQUAL(remainder(a0, eve::minf(as<T>())), a0);
  TTS_IEEE_EQUAL(remainder(eve::nan(as<T>()), a1), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(remainder(a0, eve::nan(as<T>())), eve::nan(as<T>()));
};
