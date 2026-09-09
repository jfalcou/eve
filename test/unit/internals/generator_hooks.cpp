//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// eve converts a generator's bounds to the target type before drawing: these pin that the values
// coming back stay inside them.
//==================================================================================================

TTS_CASE_WITH("randoms stays inside a narrow positive range",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(0.01, 1.0))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_GREATER_EQUAL(eve::minimum(a0), v_t(0.01));
  TTS_LESS_EQUAL(eve::maximum(a0), v_t(1.0));
};

TTS_CASE_WITH("randoms stays inside a range straddling zero",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(-2.0, 3.0))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPECT(eve::all(a0 >= v_t(-2.0)));
  TTS_EXPECT(eve::all(a0 <= v_t(3.0)));
};

TTS_CASE_WITH("randoms stays inside the limits of its own type",
              eve::test::simd::ieee_reals_wf16,
              tts::randoms(eve::valmin, eve::valmax))
<typename T>(T const& a0)
{
  TTS_EXPECT(eve::all(eve::is_finite(a0)));
};

TTS_CASE_WITH("randoms stays inside its bounds on signed integral lanes",
              eve::test::simd::signed_integers,
              tts::randoms(-100, 100))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_GREATER_EQUAL(eve::minimum(a0), v_t(-100));
  TTS_LESS_EQUAL(eve::maximum(a0), v_t(100));
};

// TTS asserts an unsigned generator never gets a negative lower bound.
TTS_CASE_WITH("randoms stays inside its bounds on unsigned integral lanes",
              eve::test::simd::unsigned_integers,
              tts::randoms(1, 100))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  TTS_GREATER_EQUAL(eve::minimum(a0), v_t(1));
  TTS_LESS_EQUAL(eve::maximum(a0), v_t(100));
};

TTS_CASE_WITH("logicals draws both values and nothing else",
              eve::test::simd::ieee_reals,
              tts::logicals(0, 3))
<typename T>(eve::logical<T> const& m)
{
  TTS_EXPECT(eve::all(m || !m));
};

TTS_CASE("tts::generation<eve::wide> fills every lane, not just the first")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  auto v = tts::generation<w_t>::make(tts::value(3));

  TTS_TYPE_IS(decltype(v), w_t);
  TTS_EQUAL(v, (w_t{3, 3, 3, 3}));
};

//==================================================================================================
//==================================================================================================
TTS_CASE("tts::generation<eve::float16_t> draws against float16's own bounds")
{
  auto v = tts::generation<eve::float16_t>::make(tts::randoms(eve::valmin, eve::valmax));

  TTS_TYPE_IS(decltype(v), eve::float16_t);
  TTS_EXPECT(eve::is_finite(v));
};

TTS_CASE("tts::generation of a float16 register keeps every lane finite")
{
  using w_t = eve::wide<eve::float16_t, eve::fixed<4>>;

  auto v = tts::generation<w_t>::make(tts::randoms(eve::valmin, eve::valmax));

  TTS_TYPE_IS(decltype(v), w_t);
  TTS_EXPECT(eve::all(eve::is_finite(v)));
};

//==================================================================================================
//==================================================================================================
TTS_CASE("tts::produce routes the EVE shapes through the trait")
{
  using w_t = eve::wide<std::int32_t, eve::fixed<4>>;

  TTS_EQUAL( tts::produce(tts::type<w_t>{}, tts::value(7))
           , tts::generation<w_t>::make(tts::value(7))
           );

  TTS_EQUAL(tts::produce(tts::type<int>{}, tts::value(7)), 7);
};

//==================================================================================================
//==================================================================================================
TTS_CASE("tts::conversion casts a plain value")
{
  TTS_EQUAL(tts::convert_as(3, tts::type<double>{}), 3.0);
  TTS_EQUAL(tts::convert_as(3.7, tts::type<int>{}), 3);

  TTS_TYPE_IS(decltype(tts::convert_as(3, tts::type<double>{})), double);
};

TTS_CASE("tts::conversion evaluates a constant against the type asked for")
{
  TTS_EQUAL(tts::convert_as(eve::valmax, tts::type<std::int8_t>{}),  std::int8_t(127));
  TTS_EQUAL(tts::convert_as(eve::valmax, tts::type<std::int16_t>{}), std::int16_t(32767));

  TTS_EQUAL(tts::convert_as(eve::one,  tts::type<float>{}),  1.0f);
  TTS_EQUAL(tts::convert_as(eve::mone, tts::type<double>{}), -1.0);
};

TTS_CASE("tts::conversion evaluates a constant against a register too")
{
  using w_t = eve::wide<float, eve::fixed<4>>;

  auto v = tts::convert_as(eve::valmax, tts::type<w_t>{});

  TTS_TYPE_IS(decltype(v), w_t);
  TTS_EXPECT(eve::all(v == eve::valmax(eve::as<w_t>{})));
};

TTS_CASE("tts::convert_as routes through the trait")
{
  TTS_EQUAL( tts::convert_as(eve::valmax, tts::type<float>{})
           , (tts::conversion<float, decltype(eve::valmax)>::from(eve::valmax))
           );
};
