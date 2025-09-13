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

  // pedantic
  TTS_EXPR_IS(hypot[pedantic](T(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](T(), v_t()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](T(), int()), T);
  TTS_EXPR_IS(hypot[pedantic](int(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), v_t()), v_t);

  // multi
  TTS_EXPR_IS(hypot[pedantic](T(), T(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](T(), v_t(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), T(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](T(), T(), v_t()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), v_t(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), T(), v_t()), T);

  TTS_EXPR_IS(hypot[pedantic](T(), int(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](int(), T(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](T(), T(), int()), T);
  TTS_EXPR_IS(hypot[pedantic](int(), v_t(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](int(), T(), v_t()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), int(), T()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), T(), int()), T);
  TTS_EXPR_IS(hypot[pedantic](v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== hypot tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of hypot(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10000.0, 10000.0),
                            tts::randoms(-10000.0, 10000.0),
                            tts::randoms(-10000.0, 10000.0)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::hypot;
  using eve::pedantic;
  using eve::raw;
  using eve::kahan;

  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      hypot(a0, a1), tts::map([](auto e, auto f) -> v_t { return std::hypot(e, f); }, a0, a1), 1.5) << a0 << " -- " << a1 << '\n';
  TTS_ULP_EQUAL(
    hypot[eve::pedantic](a0, a1), tts::map([](auto e, auto f) -> v_t { return std::hypot(e, f); }, a0, a1), 0.5);
  TTS_ULP_EQUAL(
    hypot[eve::raw](a0, a1), tts::map([](auto e, auto f) -> v_t { return std::hypot(e, f); }, a0, a1), 0.5);
  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(hypot(a0, a1, a2),
                  tts::map([](auto e, auto f, auto g) { return std::hypot(e, f, g); }, a0, a1, a2),
                  2);
    TTS_ULP_EQUAL(hypot[pedantic](a0, a1, a2),
                  tts::map([](auto e, auto f, auto g) { return std::hypot(e, f, g); }, a0, a1, a2),
                  2);
    TTS_ULP_EQUAL(hypot(kumi::tuple{a0, a1, a2}),
                  tts::map([](auto e, auto f, auto g) { return std::hypot(e, f, g); }, a0, a1, a2),
                  2);
    TTS_ULP_EQUAL(hypot[pedantic](kumi::tuple{a0, a1, a2}),
                  tts::map([](auto e, auto f, auto g) { return std::hypot(e, f, g); }, a0, a1, a2),
                  2);
     TTS_ULP_EQUAL(hypot[kahan](kumi::tuple{a0, a1, a2}),
                  tts::map([](auto e, auto f, auto g) { return std::hypot(e, f, g); }, a0, a1, a2),
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
#ifdef SPY_ARCH_IS_ARM
  TTS_IEEE_EQUAL(eve::hypot(cases.nan, a0), cases.nan);
  TTS_EQUAL(eve::hypot(cases.minf, a0), cases.inf);
  TTS_EQUAL(eve::hypot(cases.mzero, cases.mzero), T(0));
  TTS_EQUAL(eve::hypot[eve::raw](cases.valmax / 2, cases.valmax / 2), cases.inf);
  TTS_EQUAL(eve::hypot[eve::raw](cases.valmin / 2, cases.valmin / 2), cases.inf);
  TTS_EQUAL(eve::hypot[eve::pedantic](cases.mzero, cases.mzero), T(0));
#else
  TTS_IEEE_EQUAL(eve::hypot[eve::pedantic](cases.nan, a0), cases.nan);
  TTS_EQUAL(eve::hypot[eve::pedantic](cases.minf, a0), cases.inf);
  TTS_EQUAL(eve::hypot[eve::pedantic](cases.nan, cases.minf), cases.inf);
  TTS_EQUAL(eve::hypot[eve::pedantic](cases.inf, cases.nan), cases.inf);
  TTS_EQUAL(eve::hypot[eve::pedantic](cases.mzero, cases.mzero), T(0));
  TTS_ULP_EQUAL(eve::hypot[eve::pedantic](cases.valmin / 2, cases.valmin / 2),
                cases.valmax / eve::sqrt_2(eve::as<T>()), 1) << cases.valmin / 2 << '\n';
  TTS_ULP_EQUAL(eve::hypot[eve::pedantic](cases.valmax / 2, cases.valmax / 2),
                cases.valmax / eve::sqrt_2(eve::as<T>()), 1)<< cases.valmin / 2 << '\n';
  TTS_ULP_EQUAL(eve::hypot[eve::pedantic](cases.valmax, cases.valmin),
                cases.valmax, 1)<< cases.valmax<< '\n';
  TTS_ULP_EQUAL(eve::hypot[eve::pedantic](cases.smallestposval*2, cases.smallestposval),
                cases.smallestposval*eve::sqrt(T(5)), 1)<< cases.smallestposval<< '\n';
  TTS_ULP_EQUAL(eve::hypot[eve::pedantic](cases.smallestposval, cases.smallestposval),
                cases.smallestposval*eve::sqrt_2(eve::as<T>()), 1)<< cases.smallestposval<< '\n';
  TTS_IEEE_EQUAL(eve::hypot[eve::raw](cases.nan, a0), cases.nan);
  TTS_IEEE_EQUAL(eve::hypot[eve::raw](cases.minf, a0), cases.inf);
  TTS_IEEE_EQUAL(eve::hypot[eve::raw](cases.nan, cases.minf), cases.nan);
  TTS_IEEE_EQUAL(eve::hypot[eve::raw](cases.inf, cases.nan), cases.nan);
  TTS_IEEE_EQUAL(eve::hypot[eve::raw](cases.mzero, cases.mzero), T(0));
  TTS_IEEE_EQUAL(eve::hypot(cases.nan, a0), cases.nan);
  TTS_IEEE_EQUAL(eve::hypot(cases.minf, a0), cases.inf);
  TTS_IEEE_EQUAL(eve::hypot(cases.nan, cases.minf), cases.inf);
  TTS_IEEE_EQUAL(eve::hypot(cases.inf, cases.nan), cases.inf);
  TTS_IEEE_EQUAL(eve::hypot(cases.mzero, cases.mzero), T(0));
#endif
                };


//==================================================================================================
//== Tests for masked hypot
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::hypot)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::hypot[mask](a0, a1),
            eve::if_else(mask, eve::hypot(a0, a1), a0));
};
