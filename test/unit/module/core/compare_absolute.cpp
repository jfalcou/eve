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
TTS_CASE_TPL("Check return types of eve::compare_absolute(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  auto f = eve::is_greater;
  TTS_EXPR_IS(eve::compare_absolute(T(), T(), f), logical<T>);
  TTS_EXPR_IS(eve::compare_absolute(v_t(), v_t(), f), logical<v_t>);
  TTS_EXPR_IS(eve::compare_absolute(T(), v_t(), f), logical<T>);
  TTS_EXPR_IS(eve::compare_absolute(v_t(), T(), f), logical<T>);
  TTS_EXPR_IS(eve::compare_absolute[eve::saturated](T(), T(), f), logical<T>);
  TTS_EXPR_IS(eve::compare_absolute[eve::saturated](v_t(), v_t(), f), logical<v_t>);
  TTS_EXPR_IS(eve::compare_absolute[eve::saturated](T(), v_t(), f), logical<T>);
  TTS_EXPR_IS(eve::compare_absolute[eve::saturated](v_t(), T(), f), logical<T>);

};

//==================================================================================================
//== Tests for eve::compare_absolute
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::compare_absolute(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::ramp(0), tts::reverse_ramp(4, 2), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, T const& a1, M const& t)
{
  using v_t = eve::element_type_t<T>;
  auto ff = eve::is_greater;
  TTS_EQUAL(eve::compare_absolute(a0, a1, ff),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return eve::abs(e) > eve::abs(f); }, a0, a1));
  TTS_EQUAL(eve::compare_absolute(a0, a0, ff),
            tts::map([](auto e, auto f) -> eve::logical<v_t> { return eve::abs(e) > eve::abs(f); }, a0, a0));
  TTS_EQUAL(eve::compare_absolute(a0, v_t(1), ff),
            tts::map([](auto e) -> eve::logical<v_t> { return eve::abs(e) > v_t(1); }, a0));
  TTS_EQUAL(eve::compare_absolute[t](a0, a1, ff),
            eve::if_else(t, eve::compare_absolute(a0, a1, ff), eve::false_(eve::as(a0))));
  auto gg =  eve::is_gtz;
 TTS_EQUAL(eve::compare_absolute(a0, gg),
            tts::map([](auto e) -> eve::logical<v_t> { return eve::abs(e) > v_t(0); }, a0));
  TTS_EQUAL(eve::compare_absolute[t](a0, gg),
            eve::if_else(t, eve::compare_absolute(a0, gg), eve::false_(eve::as(a0))));
};
