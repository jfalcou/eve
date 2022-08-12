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
TTS_CASE_TPL("Check return types of hypot", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::hypot;
  using eve::pedantic;

  // regular
  TTS_EXPR_IS(hypot(T(), T()), T);
  TTS_EXPR_IS(hypot(T(), v_t()), T);
  TTS_EXPR_IS(hypot(v_t(), T()), T);
  TTS_EXPR_IS(hypot(T(), int()), T);
  TTS_EXPR_IS(hypot(int(), T()), T);
  TTS_EXPR_IS(hypot(v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(hypot(T(), T(), T()), T);
  TTS_EXPR_IS(hypot(T(), v_t(), T()), T);
  TTS_EXPR_IS(hypot(v_t(), T(), T()), T);
  TTS_EXPR_IS(hypot(T(), T(), v_t()), T);
  TTS_EXPR_IS(hypot(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(hypot(v_t(), T(), v_t()), T);

  TTS_EXPR_IS(hypot(T(), int(), T()), T);
  TTS_EXPR_IS(hypot(int(), T(), T()), T);
  TTS_EXPR_IS(hypot(T(), T(), int()), T);
  TTS_EXPR_IS(hypot(int(), v_t(), T()), T);
  TTS_EXPR_IS(hypot(int(), T(), v_t()), T);
  TTS_EXPR_IS(hypot(v_t(), int(), T()), T);
  TTS_EXPR_IS(hypot(v_t(), T(), int()), T);
  TTS_EXPR_IS(hypot(v_t(), v_t(), v_t()), v_t);

  // regular
  TTS_EXPR_IS(pedantic(hypot)(T(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(T(), v_t()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(T(), int()), T);
  TTS_EXPR_IS(pedantic(hypot)(int(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(pedantic(hypot)(T(), T(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(T(), v_t(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), T(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(T(), T(), v_t()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), T(), v_t()), T);

  TTS_EXPR_IS(pedantic(hypot)(T(), int(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(int(), T(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(T(), T(), int()), T);
  TTS_EXPR_IS(pedantic(hypot)(int(), v_t(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(int(), T(), v_t()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), int(), T()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), T(), int()), T);
  TTS_EXPR_IS(pedantic(hypot)(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== hypot tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of hypot(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0),
                            tts::randoms(-100.0, 100.0),
                            tts::randoms(-100.0, 100.0)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::hypot;
  using eve::pedantic;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      hypot(a0, a1), map([](auto e, auto f) -> v_t { return std::hypot(e, f); }, a0, a1), 2);
  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(hypot(a0, a1, a2),
                  map([](auto e, auto f, auto g) { return std::hypot(e, f, g); }, a0, a1, a2),
                  2);
    TTS_ULP_EQUAL(pedantic(hypot)(a0, a1, a2),
                  map([](auto e, auto f, auto g) { return std::hypot(e, f, g); }, a0, a1, a2),
                  2);
  }
};

//==================================================================================================
//== Test for corner-cases values
//==================================================================================================
TTS_CASE_WITH("Check corner-cases behavior of eve::hypot variants on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-100.0, 100.0)))
<typename T>(T const& a0)
{
  auto cases = tts::limits(tts::type<T> {});

  TTS_IEEE_EQUAL(eve::hypot(cases.nan, a0), cases.nan);
  TTS_EQUAL(eve::hypot(cases.minf, a0), cases.inf);
  TTS_EQUAL(eve::hypot(cases.mzero, cases.mzero), T(0));
  TTS_EQUAL(eve::hypot(cases.valmax / 2, cases.valmax / 2), cases.inf);
  TTS_EQUAL(eve::hypot(cases.valmin / 2, cases.valmin / 2), cases.inf);
  TTS_EQUAL(eve::pedantic(eve::hypot)(cases.mzero, cases.mzero), T(0));

  TTS_IEEE_EQUAL(eve::pedantic(eve::hypot)(cases.nan, a0), cases.nan);
  TTS_EQUAL(eve::pedantic(eve::hypot)(cases.minf, a0), cases.inf);
  TTS_EQUAL(eve::pedantic(eve::hypot)(cases.nan, cases.minf), cases.inf);
  TTS_EQUAL(eve::pedantic(eve::hypot)(cases.inf, cases.nan), cases.inf);

  TTS_EQUAL(eve::pedantic(eve::hypot)(cases.mzero, cases.mzero), T(0));
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(cases.valmin / 2, cases.valmin / 2),
                cases.valmax / eve::sqrt_2(eve::as<T>()),
                2);
  TTS_ULP_EQUAL(eve::pedantic(eve::hypot)(cases.valmax / 2, cases.valmax / 2),
                cases.valmax / eve::sqrt_2(eve::as<T>()),
                2);
  ;
};
