//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of average", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::average(T(), T()), T);
  TTS_EXPR_IS(eve::average(T(), v_t()), T);
  TTS_EXPR_IS(eve::average(v_t(), T()), T);
  TTS_EXPR_IS(eve::average(T(), int()), T);
  TTS_EXPR_IS(eve::average(int(), T()), T);
  TTS_EXPR_IS(eve::average(v_t(), v_t()), v_t);

  // multi
  if constexpr( eve::floating_ordered_value<T> )
  {
    TTS_EXPR_IS(eve::average(T(), T(), T()), T);
    TTS_EXPR_IS(eve::average(T(), v_t(), T()), T);
    TTS_EXPR_IS(eve::average(v_t(), T(), T()), T);
    TTS_EXPR_IS(eve::average(T(), T(), v_t()), T);
    TTS_EXPR_IS(eve::average(v_t(), v_t(), T()), T);
    TTS_EXPR_IS(eve::average(v_t(), T(), v_t()), T);

    TTS_EXPR_IS(eve::average(T(), int(), T()), T);
    TTS_EXPR_IS(eve::average(int(), T(), T()), T);
    TTS_EXPR_IS(eve::average(T(), T(), int()), T);
    TTS_EXPR_IS(eve::average(int(), v_t(), T()), T);
    TTS_EXPR_IS(eve::average(int(), T(), v_t()), T);
    TTS_EXPR_IS(eve::average(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::average(v_t(), T(), int()), T);
    TTS_EXPR_IS(eve::average(v_t(), v_t(), v_t()), v_t);
  }
};

//==================================================================================================
//== average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of average(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::average;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      average(a0, a1), map([](auto e, auto f) -> v_t { return std::midpoint(e, f); }, a0, a1), 2);
  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(average(a0, a1, a2),
                  map([](auto e, auto f, auto g) { return (g + f + e) / 3; }, a0, a1, a2),
                  48);
  }
};

TTS_CASE_WITH("Check behavior of average(wide)",
              eve::test::simd::integers,
              tts::generate(tts::randoms(-10, +10), tts::randoms(-10, +10), tts::randoms(-10, +10)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::average;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      average(a0, a1), map([](auto e, auto f) -> v_t { return std::midpoint(e, f); }, a0, a1), 2);
  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(average(a0, a1, a2),
                  map([](auto e, auto f, auto g) { return (g + f + e) / 3; }, a0, a1, a2),
                  16);
    TTS_ULP_EQUAL(average(kumi::tuple{a0, a1, a2}),
                  map([](auto e, auto f, auto g) { return (g + f + e) / 3; }, a0, a1, a2),
                  16);
  }
};

//==================================================================================================
//==  conditional average tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of  average[cond](wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(0, 127), tts::randoms(0, 127), tts::randoms(0, 127)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::average;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  // values can differ by one on integral types from scalar to simd implementations (intrinsics may
  // be at work)
  TTS_ULP_EQUAL(
      average[a2 > T(64)](a0, a1),
      map([](auto e, auto f, auto g) { return g > v_t(64) ? average(e, f) : e; }, a0, a1, a2),
      2);
};


//==================================================================================================
// Tests for masked average
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::average)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::average[mask](a0, a1),
            eve::if_else(mask, eve::average(a0, a1), a0));
};
