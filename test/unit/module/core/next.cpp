//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::next", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t  = eve::element_type_t<T>;
  using i_t  = eve::as_integer_t<T, signed>;
  using u_t  = eve::as_integer_t<T, unsigned>;
  using si_t = eve::as_integer_t<v_t, signed>;
  using su_t = eve::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::next(T()), T);
  TTS_EXPR_IS(eve::next(T(), i_t()), T);
  TTS_EXPR_IS(eve::next(T(), u_t()), T);
  TTS_EXPR_IS(eve::next(T(), si_t()), T);
  TTS_EXPR_IS(eve::next(T(), su_t()), T);
};

//==================================================================================================
// Tests for eve::next
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::next(eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(-10, +10), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  if constexpr( eve::floating_real_value<v_t> )
  {
    auto n = [](auto e) -> v_t { return std::nextafter(e, eve::valmax(eve::as(e))); };
    TTS_EQUAL(eve::next(a0), map(n, a0));
    auto nn = [n](auto e) -> v_t { return n(n(e)); };
    TTS_EQUAL(eve::next(a0, 2), map(nn, a0));
  }
  else
  {
    TTS_EQUAL(eve::next(a0), eve::inc(a0));
    TTS_EQUAL(eve::next(a0, 2), eve::inc(eve::inc(a0)));
  }
  TTS_EQUAL(eve::next[t](a0), eve::if_else(t, eve::next(a0), a0));
  TTS_EQUAL(eve::next[t](a0, 2), eve::if_else(t, eve::next(a0, 2), a0));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::next variants on wide",
             eve::test::simd::all_types)
<typename T>(tts::type<T> const& tgt)
{
  using eve::next;
  using eve::pedantic;
  using eve::saturated;

  auto cases = tts::limits(tgt);

  if constexpr( eve::floating_real_value<T> )
  {
    TTS_IEEE_EQUAL(next(cases.nan), cases.nan);
    TTS_IEEE_EQUAL(next(cases.minf), cases.valmin);
    TTS_IEEE_EQUAL(next(cases.inf), cases.nan);

    if constexpr( eve::platform::supports_denormals )
    {
      TTS_EQUAL(next(cases.mzero), cases.mindenormal);
      TTS_EQUAL(next(cases.zero), cases.mindenormal);
      TTS_EQUAL(next(-cases.mindenormal), cases.mzero);
      TTS_EQUAL(next(cases.valmax), cases.inf);
    }

    TTS_EQUAL(next(T(-1)), T(-1) + eve::eps(eve::as<T>()) / 2);
    TTS_EQUAL(next(T(1)), T(1) + eve::eps(eve::as<T>()));

    TTS_IEEE_EQUAL(pedantic(next)(cases.nan), cases.nan);
    TTS_IEEE_EQUAL(pedantic(next)(cases.minf), cases.valmin);
    TTS_IEEE_EQUAL(pedantic(next)(cases.inf), cases.nan);
    TTS_EQUAL(pedantic(next)(cases.mzero), cases.zero);

    if constexpr( eve::platform::supports_denormals )
    {
      TTS_EQUAL(pedantic(next)(cases.zero), cases.mindenormal);
      TTS_EQUAL(pedantic(next)(-cases.mindenormal), cases.mzero);
    }

    TTS_EQUAL(pedantic(next)(cases.valmax), cases.inf);
    TTS_EQUAL(pedantic(next)(T(-1)), T(-1) + eve::eps(eve::as<T>()) / 2);
    TTS_EQUAL(pedantic(next)(T(1)), T(1) + eve::eps(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(next(T(0)), T(1));
    TTS_EQUAL(next(T(1)), T(2));
    TTS_EQUAL(saturated(next)(T(0)), T(1));
    TTS_EQUAL(saturated(next)(T(1)), T(2));
    TTS_EQUAL(saturated(next)(cases.valmax), cases.valmax);
  }
};

TTS_CASE_TPL("Check corner-cases behavior of eve::next with 2 parameters",
             eve::test::simd::all_types)
<typename T>(tts::type<T> const& tgt)
{
  using eve::next;
  using eve::pedantic;
  using eve::saturated;

  auto cases = tts::limits(tgt);

  if constexpr( eve::floating_real_value<T> )
  {
    TTS_IEEE_EQUAL(next(cases.nan, 2), cases.nan);
    TTS_IEEE_EQUAL(next(cases.minf, 2), next(cases.valmin));
    TTS_IEEE_EQUAL(next(cases.inf, 2), cases.nan);

    if constexpr( eve::platform::supports_denormals )
    {
      TTS_EQUAL(next(cases.mzero, 2), next(cases.mindenormal));
      TTS_EQUAL(next(cases.zero, 2), next(cases.mindenormal));
      TTS_EQUAL(next(-cases.mindenormal, 2), cases.mindenormal);
    }

    TTS_IEEE_EQUAL(next(cases.valmax, 2), cases.nan);
    TTS_EQUAL(next(T(-1), 2), T(-1) + eve::eps(eve::as<T>()));
    TTS_EQUAL(next(T(1), 2), T(1) + eve::eps(eve::as<T>()) * 2);

    TTS_IEEE_EQUAL(pedantic(next)(cases.nan, 2), cases.nan);
    TTS_IEEE_EQUAL(pedantic(next)(cases.minf, 2), next(cases.valmin));
    TTS_IEEE_EQUAL(pedantic(next)(cases.inf, 2), cases.nan);
    if constexpr( eve::platform::supports_denormals )
    {
      TTS_EQUAL(pedantic(next)(cases.mzero, 2), cases.mindenormal);
      TTS_EQUAL(pedantic(next)(cases.zero, 2), next(cases.mindenormal));
      TTS_EQUAL(pedantic(next)(-cases.mindenormal, 2), cases.mzero);
    }

    TTS_IEEE_EQUAL(pedantic(next)(cases.valmax, 2), cases.nan);
    TTS_EQUAL(pedantic(next)(T(-1), 2), T(-1) + eve::eps(eve::as<T>()));
    TTS_EQUAL(pedantic(next)(T(1), 2), T(1) + eve::eps(eve::as<T>()) * 2);
  }
  else
  {
    TTS_EQUAL(next(T(0), 2), T(2));
    TTS_EQUAL(next(T(1), 2), T(3));
    TTS_EQUAL(saturated(next)(T(0), 2), T(2));
    TTS_EQUAL(saturated(next)(T(1), 2), T(3));
    TTS_EQUAL(saturated(next)(cases.valmax, 2), cases.valmax);
  }
};
