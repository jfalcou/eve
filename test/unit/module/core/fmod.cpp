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
TTS_CASE_TPL("Check return types of fmod", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::fmod;

  // regular
  TTS_EXPR_IS(fmod(T(), T()), T);
  TTS_EXPR_IS(fmod(T(), v_t()), T);
  TTS_EXPR_IS(fmod(v_t(), T()), T);
  TTS_EXPR_IS(fmod(v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(fmod[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(fmod[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(fmod[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(fmod[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(fmod[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(fmod[eve::logical<v_t>()](v_t(), T()), T);
  TTS_EXPR_IS(fmod[eve::logical<v_t>()](v_t(), v_t()), v_t);
};

//==================================================================================================
//==  fmod simd tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of fmod on wide",
              eve::test::simd::ieee_reals
              ,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
<typename T>(T a0, T a1)
{
  using eve::fmod;
  using eve::detail::map;

  auto thrs = std::same_as<eve::element_type_t<T>, float> ? 5e-4 : 5e-12;
  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_RELATIVE_EQUAL(fmod(a0, a1), map([](auto e, auto f) { return std::fmod(e, f); }, a0, a1), thrs) << "a0" << a0 << " a1 " << a1 << '\n';
};

TTS_CASE_WITH("Check behavior of fmod on wide corner cases",
              eve::test::simd::ieee_reals
              ,
              tts::generate(tts::randoms(1, 100),
                            tts::randoms(1, 100)))
<typename T>(T a0, T a1)
{
  using eve::fmod;
  using eve::detail::map;
  using eve::as;

  TTS_IEEE_EQUAL(fmod(T(0), a1), T(0));
  TTS_IEEE_EQUAL(fmod(-T(0), a1), T(0));
  TTS_IEEE_EQUAL(fmod(eve::inf(as<T>()), a1), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(fmod(eve::minf(as<T>()), a1), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(fmod(a0, eve::zero(as<T>())), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(fmod(a0, eve::mzero(as<T>())), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(fmod(a0, eve::inf(as<T>())), a0);
  TTS_IEEE_EQUAL(fmod(a0, eve::minf(as<T>())), a0);
  TTS_IEEE_EQUAL(fmod(eve::nan(as<T>()), a1), eve::nan(as<T>()));
  TTS_IEEE_EQUAL(fmod(a0, eve::nan(as<T>())), eve::nan(as<T>()));
};
