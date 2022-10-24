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
TTS_CASE_TPL("Check return types of negabsmax", eve::test::simd::signed_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::negabsmax(T(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::negabsmax(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::negabsmax(T(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmax(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(T(), v_t(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::negabsmax(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== negabsmax tests
//==================================================================================================

TTS_CASE_WITH("Check behavior of negabsmax on all types full range",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::abs;
  using eve::negabsmax;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto m = [](auto a, auto b, auto c) -> v_t { return -eve::abs(eve::max(a, b, c)); };
  TTS_ULP_EQUAL(negabsmax((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(negabsmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric(negabsmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(negabsmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(negabsmax(kumi::tuple{(a0), (a1), (a2)}), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(negabsmax)(kumi::tuple{(a0), (a1), (a2)}), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric(negabsmax)(kumi::tuple{(a0), (a1), (a2)}), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(negabsmax)(kumi::tuple{(a0), (a1), (a2)}), map(m, a0, a1, a2), 2);

  TTS_IEEE_EQUAL(negabsmax[t](a0, a1), eve::if_else(t, negabsmax(a0, a1), a0));
};

TTS_CASE_TPL("Check values of negabsmax", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(eve::nan(eve::as<T>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(eve::nan(eve::as<v_t>()), T(1)),
                 eve::nan(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(eve::nan(eve::as<T>()), v_t(1)),
                 eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negabsmax)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negabsmax)(T(0), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)((eve::nan(eve::as<T>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)((eve::nan(eve::as<v_t>())), T(1)), T(-1));
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)((eve::nan(eve::as<T>())), v_t(1)), T(-1));

  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)(T(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)(v_t(1), eve::nan(eve::as<T>())), T(-1));
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)(T(1), eve::nan(eve::as<v_t>())), T(-1));

  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negabsmax)(T(-0.), T(0)))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negabsmax)(T(0), T(-0.)))));
};
