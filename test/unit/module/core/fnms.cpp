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
TTS_CASE_TPL("Check return types of fnms", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::fnms(T(), T(), T()), T);
  TTS_EXPR_IS(eve::fnms(T(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fnms(v_t(), T(), T()), T);
  TTS_EXPR_IS(eve::fnms(T(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fnms(v_t(), v_t(), T()), T);
  TTS_EXPR_IS(eve::fnms(v_t(), T(), v_t()), T);
  TTS_EXPR_IS(eve::fnms(v_t(), v_t(), v_t()), v_t);

  if constexpr( eve::floating_value<T> )
  {
    using wi_t = eve::as_wide_t<int, eve::cardinal_t<T>>;
    TTS_EXPR_IS(eve::fnms(T(), int(), int()), T);
    TTS_EXPR_IS(eve::fnms(T(), v_t(), int()), T);
    TTS_EXPR_IS(eve::fnms(v_t(), int(), T()), T);
    TTS_EXPR_IS(eve::fnms(int(), T(), int()), T);
    TTS_EXPR_IS(eve::fnms(wi_t(), int(), int()), wi_t);
    TTS_EXPR_IS(eve::fnms(char(), wi_t(), int()), wi_t);
  }
};

//==================================================================================================
// fnms tests
//==================================================================================================
auto onepmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::inc(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

auto onemmileps =
    tts::constant([]<typename U>(eve::as<U>)
                  { return (eve::oneminus(1000 * eve::eps(eve::as(eve::element_type_t<U>())))); });

TTS_CASE_WITH("Check precision behavior of fnms on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(onemmileps, onepmileps),
                            tts::randoms(onemmileps, onepmileps)))
<typename T>(T const& a0, T const& a1)
{
  using eve::fnms;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      eve::pedantic(fnms)(a0, a1, eve::one(eve::as<T>())),
      map([&](auto e, auto f) -> v_t { return eve::pedantic(fnms)(e, f, v_t(1)); }, a0, a1),
      2);
};

//==================================================================================================
// fnms full range tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of fnms on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::as;
  using eve::fnms;
  using eve::detail::map;

  using v_t = eve::element_type_t<T>;
  if( eve::all(
          eve::fnms(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(1))
          == eve::pedantic(eve::fnms)(onemmileps(eve::as(a0)), onepmileps(eve::as(a0)), T(1))) )
  {
    TTS_ULP_EQUAL(fnms((a0), (a1), (a2)),
                  map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fnms)(e, f, g); },
                      a0,
                      a1,
                      a2),
                  2);
  }
  else
  {
    TTS_ULP_EQUAL(fnms((a0), (a1), (a2)),
                  map([&](auto e, auto f, auto g) -> v_t { return -e * f + g; }, a0, a1, a2),
                  2);
  }
  TTS_ULP_EQUAL(
      eve::pedantic(fnms)((a0), (a1), (a2)),
      map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fnms)(e, f, g); }, a0, a1, a2),
      2);
  TTS_ULP_EQUAL(
      eve::numeric(fnms)((a0), (a1), (a2)),
      map([&](auto e, auto f, auto g) -> v_t { return eve::pedantic(fnms)(e, f, g); }, a0, a1, a2),
      2);
};

//==================================================================================================
// fnms masked
//==================================================================================================
TTS_CASE_WITH("Check behavior of fnms on all types full range",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const& t)
{
  using eve::as;
  using eve::fnms;

  TTS_IEEE_EQUAL(fnms[t](a0, a1, a2), eve::if_else(t, fnms[t](a0, a1, a2), a0));
};
