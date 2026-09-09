//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// tts::display is what a failing assertion prints: these pin the text character for character.
//==================================================================================================

TTS_CASE("tts::display<eve::wide> lists the lanes in order")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  TTS_EQUAL(tts::as_text(w_t{1, 2, 3, 4}), "(1, 2, 3, 4)");
  TTS_EQUAL(tts::as_text(w_t{4, 3, 2, 1}), "(4, 3, 2, 1)");

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
//==================================================================================================
TTS_CASE("tts::display<eve::float16_t> renders through double")
{
  TTS_EQUAL(tts::as_text(eve::float16_t(0.5f)),  "0.5");
  TTS_EQUAL(tts::as_text(eve::float16_t(-2.0f)), "-2");
};

TTS_CASE("tts::display renders a constant as the value it holds")
{
  TTS_EQUAL(tts::as_text(std::integral_constant<int, 42>{}), "42");
  TTS_EQUAL(tts::as_text(std::integral_constant<std::size_t, 7>{}), "7");
};

//==================================================================================================
//==================================================================================================
TTS_CASE("tts::as_text routes the EVE shapes through the trait")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  w_t const v {1, 2, 3, 4};

  TTS_EQUAL(tts::as_text(v), tts::display<w_t>::render(v));

  TTS_EQUAL(tts::as_text(42), "42");
};
