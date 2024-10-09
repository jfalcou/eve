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
TTS_CASE_TPL("Check return types of negabsmin", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::negabsmin(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::negabsmin(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmin(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmin(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== negabsmin tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of negabsmin on all types full range",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::negabsmin;
  using v_t = eve::element_type_t<T>;

  auto m = [](auto a, auto b, auto c) -> v_t { return eve::minus[eve::saturated](eve::abs[eve::saturated](eve::min(a, b, c))); };
  TTS_ULP_EQUAL(negabsmin((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negabsmin[eve::pedantic]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negabsmin[eve::numeric]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negabsmin[eve::saturated]((a0), (a1), (a2)), tts::map(m, a0, a1, a2), 2);
//   TTS_ULP_EQUAL(negabsmin(kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);
//   TTS_ULP_EQUAL(eve::negabsmin[eve::pedantic](kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);
//   TTS_ULP_EQUAL(eve::negabsmin[eve::numeric](kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);
//   TTS_ULP_EQUAL(eve::negabsmin[eve::saturated](kumi::tuple{(a0), (a1), (a2)}), tts::map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(negabsmin[t](a0, a1), eve::if_else(t, negabsmin(a0, a1), a0));
};

TTS_CASE_TPL("Check values of negabsmin", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::negabsmin[eve::pedantic](eve::nan(eve::as<T>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::pedantic](eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::pedantic](eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::negabsmin[eve::pedantic](T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::pedantic](v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::pedantic](T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::negabsmin[eve::pedantic](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::negabsmin[eve::pedantic](T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::negabsmin[eve::numeric]((eve::nan(eve::as<T>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::numeric]((eve::nan(eve::as<v_t>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::numeric]((eve::nan(eve::as<T>())), v_t(1)), T(-1));

  TTS_IEEE_EQUAL(eve::negabsmin[eve::numeric](T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::numeric](v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negabsmin[eve::numeric](T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::negabsmin[eve::numeric](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::negabsmin[eve::numeric](T(0), T(-0.)))));
};
