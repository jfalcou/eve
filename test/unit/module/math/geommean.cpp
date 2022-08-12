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
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of geommean", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::geommean(T(), T()), T);
  TTS_EXPR_IS(eve::geommean(T(), v_t()), T);
  TTS_EXPR_IS(eve::geommean(v_t(), T()), T);
  TTS_EXPR_IS(eve::geommean(v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(eve::geommean(T(), T(), T()), T);
  TTS_EXPR_IS(eve::geommean(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::geommean(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::geommean(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::geommean(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::geommean(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::geommean(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== geommean tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of geommean(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100, 100),
                            tts::randoms(-100, 100),
                            tts::randoms(-100, 100)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::geommean;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(geommean(a0, a1),
                map(
                    [](auto e, auto f) -> v_t {
                      return (eve::sign(e) * eve::sign(f) >= 0) ? std::sqrt(e * f)
                                                                : eve::nan(eve::as<v_t>());
                    },
                    a0,
                    a1),
                2);
  TTS_ULP_EQUAL(geommean(a0, a1, a2),
                map([](auto e, auto f, auto g) { return std::cbrt(g * f * e); }, a0, a1, a2),
                30);
};
