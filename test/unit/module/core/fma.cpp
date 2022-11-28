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
TTS_CASE_TPL("Check return types of fma", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fma(T(), T(), T()), T);
  TTS_EXPR_IS(eve::fma(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fma(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fma(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fma(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fma(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fma(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::fma(T(), int(), int()), T);
    TTS_EXPR_IS(eve::fma(T(), v_t(), int()), T);
    TTS_EXPR_IS(eve::fma(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::fma(int(), T(), int()), T);
    TTS_EXPR_IS(eve::fma(wi_t(), int(), int()), wi_t);
    TTS_EXPR_IS(eve::fma(char(), wi_t(), int()), wi_t);
  }
};

//==================================================================================================
// fma tests
//==================================================================================================
auto onepmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::inc(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

auto onemmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::oneminus(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

TTS_CASE_WITH("Check precision behavior of fma on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fma;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::pedantic(fma)(a0, a1, -eve::one(eve::as<T>())),
      map([&](auto e, auto f) -> v_t { return eve::pedantic(fma)(e, f, v_t(-1)); }, a0, a1),
      2);
};

//==================================================================================================
// fma full range tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fma on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fma;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;

  if( eve::all(
          eve::fma(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(-1))
          == eve::pedantic(eve::fma)(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(-1))) )
  {
    TTS_ULP_EQUAL(
        fma((a0), (a1), (a2)),
        map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fma)(e, f, g); }, a0, a1, a2),
        12);
  }
  else
  {
    TTS_ULP_EQUAL(fma((a0), (a1), (a2)),
                  map([&](auto e, auto f, auto g) -> v_t { return e * f + g; }, a0, a1, a2),
                  2);
  }
  TTS_ULP_EQUAL(
      eve::pedantic(fma)((a0), (a1), (a2)),
      map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fma)(e, f, g); }, a0, a1, a2),
      2);
  TTS_ULP_EQUAL(
      eve::numeric(fma)((a0), (a1), (a2)),
      map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fma)(e, f, g); }, a0, a1, a2),
      2);
};

//==================================================================================================
// fma masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of fma on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::as;
  using eve::fma;

  TTS_IEEE_EQUAL(fma[t](a0, a1, a2), eve::if_else(t, fma[t](a0, a1, a2), a0));
};
