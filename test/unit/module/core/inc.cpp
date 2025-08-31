//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of inc", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::inc(T()), T);
  TTS_EXPR_IS(eve::inc(v_t()), v_t);
  TTS_EXPR_IS(eve::inc[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::inc[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::inc[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::inc[bool()](T()), T);
  TTS_EXPR_IS(eve::inc[bool()](v_t()), v_t);

  TTS_EXPR_IS(eve::inc[eve::saturated](T()), T);
  TTS_EXPR_IS(eve::inc[eve::saturated](v_t()), v_t);
  TTS_EXPR_IS(eve::inc[eve::logical<T>()][eve::saturated](T()), T);
  TTS_EXPR_IS(eve::inc[eve::logical<v_t>()][eve::saturated](T()), T);
  TTS_EXPR_IS(eve::inc[eve::logical<v_t>()][eve::saturated](v_t()), v_t);
  TTS_EXPR_IS(eve::inc[bool()][eve::saturated](T()), T);
  TTS_EXPR_IS(eve::inc[bool()][eve::saturated](v_t()), v_t);
};


//==================================================================================================
// inc(simd)  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of inc(wide) and inc[mask](wide) on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(-100, 100)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::inc(a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e + 1); }, a0));
  TTS_EQUAL(eve::inc[eve::saturated](a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e + 1); }, a0));

  using l_t = eve::as_logical_t<T>;
  l_t m = [](auto i, auto) { return i % 2 == 0; };

  TTS_EQUAL(eve::inc[m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e + 1) : e; }, a0, m));
  TTS_EQUAL(eve::inc[m][eve::saturated](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e + 1) : e; }, a0, m));
  TTS_EQUAL(eve::inc[eve::saturated][m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e + 1) : e; }, a0, m));

  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::inc[eve::lower][eve::strict](a0), eve::prev(eve::inc(a0)), 0.5);
    TTS_ULP_EQUAL(eve::inc[eve::lower][m][eve::strict](a0), eve::prev[m](eve::inc[m](a0)), 0.5);

    TTS_ULP_EQUAL(eve::inc[eve::upper][eve::strict](a0), eve::next(eve::inc(a0)), 0.5);
    TTS_ULP_EQUAL(eve::inc[eve::upper][m][eve::strict](a0), eve::next[m](eve::inc[m](a0)), 0.5);
  }
};

TTS_CASE_WITH("Check behavior of inc(wide) and inc[mask](wide) on unsigned types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(0, 100)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::inc(a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e + 1); }, a0));
  TTS_EQUAL(eve::inc[eve::saturated](a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e + 1); }, a0));

  using l_t = eve::as_logical_t<T>;
  l_t m = [](auto i, auto) { return i % 2 == 0; };

  TTS_EQUAL(eve::inc[m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e + 1) : e; }, a0, m));
  TTS_EQUAL(eve::inc[m][eve::saturated](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e + 1) : e; }, a0, m));
  TTS_EQUAL(eve::inc[eve::saturated][m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e + 1) : e; }, a0, m));
};

//==================================================================================================
//==  inc modular tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of inc mod on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0, 96))
             )
  <typename T>(T const& ra0)
{
  using eve::inc;
  using eve::mod;
  auto a0 = eve::floor(ra0);
  using e_t =  eve::element_type_t<T>;
  e_t p = 97;
  TTS_ULP_EQUAL(inc[mod = p](a0), eve::if_else(a0 == p-1, 0, a0+1), 0.5);
};

TTS_CASE_TPL("Check corner-cases behavior of inc(wide) and inc[mask](wide)", eve::test::simd::all_types)
<typename T>(tts::type<T> tgt)
{
  auto cases = tts::limits(tgt);

  using l_t = eve::as_logical_t<T>;
  l_t m = [](auto i, auto) { return i % 2 == 0; };

  if constexpr (eve::floating_value<T>)
  {
    TTS_EQUAL(eve::inc(cases.valmax), cases.valmax);
    TTS_EQUAL(eve::inc[eve::upper](cases.valmax), cases.inf);
    TTS_EQUAL(eve::inc[eve::saturated](cases.valmax), cases.valmax);

    TTS_EQUAL(eve::inc[m](cases.valmax), cases.valmax);

    TTS_EQUAL(eve::inc[m][eve::upper](cases.valmax), eve::if_else(m, cases.inf, cases.valmax));
    TTS_EQUAL(eve::inc[eve::upper][m](cases.valmax), eve::if_else(m, cases.inf, cases.valmax));

    TTS_EQUAL(eve::inc[eve::saturated][m](cases.valmax), cases.valmax);
    TTS_EQUAL(eve::inc[m][eve::saturated](cases.valmax), cases.valmax);

    TTS_IEEE_EQUAL(eve::inc(cases.inf), cases.inf);
    TTS_IEEE_EQUAL(eve::inc(cases.minf), cases.minf);
    TTS_IEEE_EQUAL(eve::inc(cases.nan), cases.nan);
  }
  else
  {
    TTS_EQUAL(eve::inc(cases.valmax), cases.valmin);

    TTS_EQUAL(eve::inc[eve::saturated](cases.valmax), cases.valmax);
    TTS_EQUAL(eve::inc[eve::saturated][m](cases.valmax), cases.valmax);
    TTS_EQUAL(eve::inc[m][eve::saturated](cases.valmax), cases.valmax);
  }
};
