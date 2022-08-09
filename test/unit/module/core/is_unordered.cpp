//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::is_unordered(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::is_unordered(T(), T()), logical<T>);
  TTS_EXPR_IS(eve::is_unordered(v_t(), v_t()), logical<v_t>);
  TTS_EXPR_IS(eve::is_unordered(T(), v_t()), logical<T>);
  TTS_EXPR_IS(eve::is_unordered(v_t(), T()), logical<T>);
};

//==================================================================================================
//== Tests for eve::is_unordered
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::is_unordered(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3)))
<typename T, typename M>(T a0, T const& a1, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  a0.set(0, eve::nan(eve::as<v_t>()));
  TTS_EQUAL(eve::is_unordered(a0, a1),
            map([](auto e, auto f) -> eve::logical<v_t> { return (e != e) || (f != f); }, a0, a1));
  TTS_EQUAL(eve::is_unordered(a0, v_t(1)),
            map([](auto e) -> eve::logical<v_t> { return (e != e); }, a0));
  TTS_EQUAL(eve::is_unordered(v_t(14), a1),
            map([](auto e) -> eve::logical<v_t> { return (e != e); }, a1));
  TTS_EQUAL(eve::is_unordered[t](a0, a1),
            eve::if_else(t, eve::is_unordered(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_unordered corner cases for floating
//==================================================================================================
TTS_CASE_TPL("Check behavior of eve::is_unordered(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> tgt)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;
  using eve::detail::map;

  auto cases = tts::limits(tgt);

  TTS_EQUAL(eve::is_unordered(cases.nan, cases.nan), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_unordered(cases.nan, T(1)), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_unordered(T(1), cases.nan), eve::true_(as<T>()));
  TTS_EQUAL(eve::is_unordered(T(1), T(1)), eve::false_(as<T>()));
  TTS_EQUAL(eve::is_unordered(T(1), v_t(1)), eve::false_(as<T>()));
};
