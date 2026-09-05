//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// tts::display is what a failing assertion prints. Nothing else in the suite reads it, and a
// specialization that stopped being selected would cost nothing until the day a test fails and the
// report shows the built-in rendering of a register, which is its address or a compilation error
// depending on the shape.
//
// So the value under test here is the text itself, character for character. tts::text compares
// against a literal, which is what makes that readable.
//==================================================================================================

TTS_CASE("tts::display<eve::wide> lists the lanes in order")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  TTS_EQUAL(tts::as_text(w_t{1, 2, 3, 4}), "(1, 2, 3, 4)");
  TTS_EQUAL(tts::as_text(w_t{4, 3, 2, 1}), "(4, 3, 2, 1)");

  // Each lane goes through as_text for its own element type, so the rendering of a lane is the
  // rendering of the scalar and the two never drift apart.
  TTS_EQUAL(tts::as_text(eve::wide<float, eve::fixed<2>>{0.5f, -1.5f}), "(0.5, -1.5)");
};

TTS_CASE("tts::display<eve::logical> spells the two values out")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  TTS_EQUAL(tts::as_text(eve::logical<float>{true}),  "true");
  TTS_EQUAL(tts::as_text(eve::logical<float>{false}), "false");

  TTS_EQUAL(tts::as_text(eve::logical<w_t>{true, false, true, true}), "(true, false, true, true)");
};

//==================================================================================================
// float16 has no formatter of its own, and the built-in path branches on std::is_floating_point_v,
// which C++20 answers false for _Float16. Rendering goes through double for that reason.
//==================================================================================================
TTS_CASE("tts::display<eve::float16_t> renders through double")
{
  // Parenthesized rather than braced: a brace checks for narrowing, and every literal narrows on
  // the way into a half.
  TTS_EQUAL(tts::as_text(eve::float16_t(0.5f)),  "0.5");
  TTS_EQUAL(tts::as_text(eve::float16_t(-2.0f)), "-2");
};

TTS_CASE("tts::display renders a constant as the value it holds")
{
  TTS_EQUAL(tts::as_text(std::integral_constant<int, 42>{}), "42");
  TTS_EQUAL(tts::as_text(std::integral_constant<std::size_t, 7>{}), "7");
};

//==================================================================================================
// tts::as_text is the entry point every failure message reaches, and the trait is what it must
// reach in turn. Naming both is the half a direct call to render cannot see.
//==================================================================================================
TTS_CASE("tts::as_text routes the EVE shapes through the trait")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  w_t const v {1, 2, 3, 4};

  TTS_EQUAL(tts::as_text(v), tts::display<w_t>::render(v));

  // A scalar keeps the built-in rendering, which is what leaves the trait an addition rather than
  // a detour every type has to pay for.
  TTS_EQUAL(tts::as_text(42), "42");
};
