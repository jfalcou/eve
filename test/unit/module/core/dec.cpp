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
TTS_CASE_TPL("Check return types of dec", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::dec(T()), T);
  TTS_EXPR_IS(eve::dec(v_t()), v_t);
  TTS_EXPR_IS(eve::dec[eve::logical<T>()](T()), T);
  TTS_EXPR_IS(eve::dec[eve::logical<v_t>()](T()), T);
  TTS_EXPR_IS(eve::dec[eve::logical<v_t>()](v_t()), v_t);
  TTS_EXPR_IS(eve::dec[bool()](T()), T);
  TTS_EXPR_IS(eve::dec[bool()](v_t()), v_t);

  TTS_EXPR_IS(eve::dec[eve::saturated](T()), T);
  TTS_EXPR_IS(eve::dec[eve::saturated](v_t()), v_t);
  TTS_EXPR_IS(eve::dec[eve::logical<T>()][eve::saturated](T()), T);
  TTS_EXPR_IS(eve::dec[eve::logical<v_t>()][eve::saturated](T()), T);
  TTS_EXPR_IS(eve::dec[eve::logical<v_t>()][eve::saturated](v_t()), v_t);
  TTS_EXPR_IS(eve::dec[bool()][eve::saturated](T()), T);
  TTS_EXPR_IS(eve::dec[bool()][eve::saturated](v_t()), v_t);
};


//==================================================================================================
// inc(simd)  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of dec(wide) and dec[mask](wide) on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(-100, 100)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::dec(a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e - 1); }, a0));
  TTS_EQUAL(eve::dec[eve::saturated](a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e - 1); }, a0));

  using l_t = eve::as_logical_t<T>;
  l_t m = [](auto i, auto) { return i % 2 == 0; };

  TTS_EQUAL(eve::dec[m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e - 1) : e; }, a0, m));
  TTS_EQUAL(eve::dec[m][eve::saturated](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e - 1) : e; }, a0, m));
  TTS_EQUAL(eve::dec[eve::saturated][m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e - 1) : e; }, a0, m));

  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::dec[eve::lower][eve::strict](a0), eve::prev(eve::dec(a0)), 0.5);
    TTS_ULP_EQUAL(eve::dec[eve::lower][m][eve::strict](a0), eve::prev[m](eve::dec[m](a0)), 0.5);

    TTS_ULP_EQUAL(eve::dec[eve::upper][eve::strict](a0), eve::next(eve::dec(a0)), 0.5);
    TTS_ULP_EQUAL(eve::dec[eve::upper][m][eve::strict](a0), eve::next[m](eve::dec[m](a0)), 0.5);
  }
};

TTS_CASE_WITH("Check behavior of dec(wide) and dec[mask](wide) on unsigned types",
              eve::test::simd::unsigned_integers,
              tts::generate(tts::randoms(1, 100)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::dec(a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e - 1); }, a0));
  TTS_EQUAL(eve::dec[eve::saturated](a0), tts::map([](auto e) -> v_t { return static_cast<v_t>(e - 1); }, a0));

  using l_t = eve::as_logical_t<T>;
  l_t m = [](auto i, auto) { return i % 2 == 0; };

  TTS_EQUAL(eve::dec[m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e - 1) : e; }, a0, m));
  TTS_EQUAL(eve::dec[m][eve::saturated](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e - 1) : e; }, a0, m));
  TTS_EQUAL(eve::dec[eve::saturated][m](a0), tts::map([](auto e, auto me) -> v_t { return me ? static_cast<v_t>(e - 1) : e; }, a0, m));
};

TTS_CASE_TPL("Check corner-cases behavior of dec(wide) and dec[mask](wide)", eve::test::simd::all_types)
<typename T>(tts::type<T> tgt)
{
  auto cases = tts::limits(tgt);

  using l_t = eve::as_logical_t<T>;
  l_t m = [](auto i, auto) { return i % 2 == 0; };

  if constexpr (eve::floating_value<T>)
  {
    TTS_EQUAL(eve::dec(cases.valmin), cases.valmin);
    TTS_EQUAL(eve::dec[eve::lower](cases.valmin), cases.minf);
    TTS_EQUAL(eve::dec[eve::saturated](cases.valmin), cases.valmin);

    TTS_EQUAL(eve::dec[m](cases.valmin), cases.valmin);

    TTS_EQUAL(eve::dec[m][eve::lower](cases.valmin), eve::if_else(m, cases.minf, cases.valmin));
    TTS_EQUAL(eve::dec[eve::lower][m](cases.valmin), eve::if_else(m, cases.minf, cases.valmin));

    TTS_EQUAL(eve::dec[eve::saturated][m](cases.valmin), cases.valmin);
    TTS_EQUAL(eve::dec[m][eve::saturated](cases.valmin), cases.valmin);

    TTS_IEEE_EQUAL(eve::dec(cases.inf), cases.inf);
    TTS_IEEE_EQUAL(eve::dec(cases.minf), cases.minf);
    TTS_IEEE_EQUAL(eve::dec(cases.nan), cases.nan);
  }
  else
  {
    TTS_EQUAL(eve::dec(cases.valmin), cases.valmax);

    TTS_EQUAL(eve::dec[eve::saturated](cases.valmin), cases.valmin);
    TTS_EQUAL(eve::dec[eve::saturated][m](cases.valmin), cases.valmin);
    TTS_EQUAL(eve::dec[m][eve::saturated](cases.valmin), cases.valmin);
  }
};
