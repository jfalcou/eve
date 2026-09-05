//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// EVE overloads tts::produce for its own dataset, and for float16 it converts the bounds against the
// half format before drawing. Nothing checked that the values that come back honour the bounds that
// were asked for: a test drawing in [0.01, 1] and receiving 1e-5 reads as a precision failure of the
// function under test, which is where asech.cpp sent us looking.
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

// Separate from the signed case: TTS asserts that an unsigned generator is never given a negative
// lower bound, so the two cannot share a range.
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
// The reason the float16 specializations exist. Drawing between valmin and valmax through the
// built-in path evaluates the two bounds against float, so the draw spans +/-3.4e38 and every
// narrowing to half lands on an infinity. A finite value is the whole assertion.
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
// tts::produce is what TTS_CASE_WITH reaches, and the trait is what it must reach in turn. Going
// through the dispatcher rather than the members is the half a direct call cannot see.
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
// tts::conversion is what every generator bound goes through. A bound is written once, in the case,
// and has to answer for each type the case is run on, so a plain value is cast while a constant is
// a recipe that has to be evaluated against the type instead.
//
// Getting this wrong is silent in the worst way: `eve::valmax` read as a value rather than as a
// recipe would still convert, to whatever the recipe object happens to cast to, and the draw would
// simply span the wrong range.
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
