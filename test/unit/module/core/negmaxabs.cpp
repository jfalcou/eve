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
TTS_CASE_TPL("Check return types of negmaxabs", eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::negmaxabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::negmaxabs(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negmaxabs(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negmaxabs(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== negmaxabs tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of negmaxabs on all types full range",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::negmaxabs;

  TTS_ULP_EQUAL(negmaxabs(a0, a1, a2), -eve::maxabs(a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negmaxabs[eve::pedantic](a0, a1, a2),  -eve::maxabs[eve::pedantic](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negmaxabs[eve::numeric](a0, a1, a2),   -eve::maxabs[eve::numeric ](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negmaxabs[eve::saturated](a0, a1, a2), -eve::maxabs[eve::saturated](a0, a1, a2), 2);
  TTS_ULP_EQUAL(negmaxabs(kumi::tuple{(a0), (a1), (a2)}), negmaxabs(a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negmaxabs[eve::pedantic](kumi::tuple{(a0), (a1), (a2)}), eve::negmaxabs[eve::pedantic](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negmaxabs[eve::numeric](kumi::tuple{(a0), (a1), (a2)}),  eve::negmaxabs[eve::numeric](a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::negmaxabs[eve::saturated](kumi::tuple{(a0), (a1), (a2)}),eve::negmaxabs[eve::saturated](a0, a1, a2), 2);

  TTS_IEEE_EQUAL(negmaxabs[t](a0, a1), eve::if_else(t, negmaxabs(a0, a1), a0));
};

TTS_CASE_TPL("Check values of negmaxabs", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::pedantic](eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::pedantic](eve::nan(eve::as<v_t>()), T(1)), eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::pedantic](eve::nan(eve::as<T>()), v_t(1)), eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::negmaxabs[eve::pedantic](T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::pedantic](v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::pedantic](T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::negmaxabs[eve::pedantic](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::negmaxabs[eve::pedantic](T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::negmaxabs[eve::numeric]((eve::nan(eve::as<T>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::numeric]((eve::nan(eve::as<v_t>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::numeric]((eve::nan(eve::as<T>())), v_t(1)), T(-1));

  TTS_IEEE_EQUAL(eve::negmaxabs[eve::numeric](T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::numeric](v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::negmaxabs[eve::numeric](T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::negmaxabs[eve::numeric](T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::negmaxabs[eve::numeric](T(0), T(-0.)))));
};
