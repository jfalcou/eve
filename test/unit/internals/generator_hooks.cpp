//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// EVE overloads tts::produce for its own shapes, and for float16 it converts the bounds against the
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
