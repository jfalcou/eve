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
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::logical_not(simd)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::logical_not(logical<T>()), logical<T>);
  TTS_EXPR_IS(eve::logical_not(logical<v_t>()), logical<v_t>);
};

//==================================================================================================
// Tests for eve::logical_not
//==================================================================================================

TTS_CASE_WITH("Check behavior of eve::logical_not(simd)",
              eve::test::simd::all_types,
              tts::generate(tts::logicals(0, 3)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::logical_not(a0), tts::map([](auto e) -> v_t { return !e; }, a0));
  TTS_EQUAL(eve::logical_not(true), false);
  TTS_EQUAL(eve::logical_not(false), true);

  auto alt = eve::false_(eve::as<T>{});
  auto base = eve::logical_not(a0);

  TTS_EQUAL(eve::logical_not[eve::ignore_all](a0), alt);
  TTS_EQUAL(eve::logical_not[eve::ignore_none](a0), base);
  TTS_EQUAL(eve::logical_not[false](a0), alt);
  TTS_EQUAL(eve::logical_not[true](a0), base);

  T m = tts::poison(T{ [](auto i, auto) { return i % 2 == 0; } });
  TTS_EQUAL(eve::logical_not[m](a0), eve::if_else(m, base, alt));

  constexpr auto cardinal = eve::cardinal_v<T>;

  if constexpr (cardinal >= 2)
  {
    TTS_EQUAL(eve::logical_not[eve::ignore_extrema(1, 1)](a0), eve::if_else(eve::ignore_extrema(1, 1), base, alt));
    TTS_EQUAL(eve::logical_not[eve::ignore_extrema(cardinal / 2, cardinal / 2)](a0), eve::if_else(eve::ignore_extrema(cardinal / 2, cardinal / 2), base, alt));
    TTS_EQUAL(eve::logical_not[eve::ignore_extrema(cardinal / 4, cardinal / 4)](a0), eve::if_else(eve::ignore_extrema(cardinal / 4, cardinal / 4), base, alt));
  }
};
