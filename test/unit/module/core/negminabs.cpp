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
TTS_CASE_TPL("Check return types of negminabs", eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::negminabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negminabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negminabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::negminabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negminabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negminabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negminabs(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negminabs(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== negminabs tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of negminabs on all types full range",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::negminabs;

  TTS_ULP_EQUAL(negminabs(a0, a1, a2), -eve::minabs(a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negminabs[eve::pedantic](a0, a1, a2),  -eve::minabs[eve::pedantic](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negminabs[eve::numeric](a0, a1, a2),   -eve::minabs[eve::numeric ](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negminabs[eve::saturated](a0, a1, a2), -eve::minabs[eve::saturated](a0, a1, a2), 2);
  TTS_ULP_EQUAL(negminabs(kumi::tuple{(a0), (a1), (a2)}), -eve::minabs(a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negminabs[eve::pedantic](kumi::tuple{(a0), (a1), (a2)}),  -eve::minabs[eve::pedantic](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negminabs[eve::numeric](kumi::tuple{(a0), (a1), (a2)}),   -eve::minabs[eve::numeric](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negminabs[eve::saturated](kumi::tuple{(a0), (a1), (a2)}), -eve::minabs[eve::saturated](a0, a1, a2), 2);

  TTS_IEEE_EQUAL(negminabs[t](a0, a1), eve::if_else(t, negminabs(a0, a1), a0));
};

TTS_CASE_TPL("Check values of negminabs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::negminabs[eve::pedantic](eve::nan(eve::as<T>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::negminabs[eve::pedantic](eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::negminabs[eve::pedantic](eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::negminabs[eve::pedantic](T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negminabs[eve::pedantic](v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negminabs[eve::pedantic](T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::negminabs[eve::pedantic](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::negminabs[eve::pedantic](T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::negminabs[eve::numeric]((eve::nan(eve::as<T>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::negminabs[eve::numeric]((eve::nan(eve::as<v_t>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::negminabs[eve::numeric]((eve::nan(eve::as<T>())), v_t(1)), T(-1));

  TTS_IEEE_EQUAL(eve::negminabs[eve::numeric](T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negminabs[eve::numeric](v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negminabs[eve::numeric](T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::negminabs[eve::numeric](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::negminabs[eve::numeric](T(0), T(-0.)))));
};
