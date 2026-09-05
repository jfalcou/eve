//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// tts::limits hands a case the notable values of the type it runs on. The built-in set is built on
// std::numeric_limits, which has nothing to say about a register: its own static_assert refuses the
// type outright.
//
// That refusal is what makes this file worth having. A specialization that stopped being selected
// would not produce wrong values, it would stop the build, so the cases below are as much about the
// members being reachable at all as about what they hold.
//==================================================================================================

TTS_CASE_TPL("tts::limits carries the EVE constants for a floating register",
             eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  auto const l = tts::limits(tts::type<T>{});

  TTS_TYPE_IS(typename decltype(l)::type, T);

  TTS_EXPECT(eve::all(eve::is_nan(l.nan)));
  TTS_EXPECT(eve::all(l.inf  == eve::inf (eve::as<T>{})));
  TTS_EXPECT(eve::all(l.minf == eve::minf(eve::as<T>{})));

  TTS_EXPECT(eve::all(l.zero  == eve::zero(eve::as<T>{})));
  TTS_EXPECT(eve::all(l.one   == eve::one (eve::as<T>{})));
  TTS_EXPECT(eve::all(l.mone  == eve::mone(eve::as<T>{})));

  TTS_EXPECT(eve::all(l.valmax == eve::valmax(eve::as<T>{})));
  TTS_EXPECT(eve::all(l.valmin == eve::valmin(eve::as<T>{})));

  TTS_EXPECT(eve::all(l.mindenormal    == eve::mindenormal   (eve::as<T>{})));
  TTS_EXPECT(eve::all(l.smallestposval == eve::smallestposval(eve::as<T>{})));
  TTS_EXPECT(eve::all(l.maxflint       == eve::maxflint      (eve::as<T>{})));

  // A negative zero compares equal to a positive one, so the value has to be read by its sign bit
  // rather than by an equality that cannot tell the two apart.
  TTS_EXPECT(eve::all(eve::is_negative(l.mzero)));
  TTS_EXPECT(eve::all(l.mzero == eve::zero(eve::as<T>{})));
};

//==================================================================================================
// The integral set holds the two bounds and nothing else, which is what the specialization it
// replaces answered. Naming the members that are absent is not possible, so the two that are
// present are pinned instead.
//==================================================================================================
TTS_CASE_TPL("tts::limits carries the two bounds for an integral register",
             eve::test::simd::integers)
<typename T>(tts::type<T>)
{
  auto const l = tts::limits(tts::type<T>{});

  TTS_TYPE_IS(typename decltype(l)::type, T);

  TTS_EXPECT(eve::all(l.valmax == eve::valmax(eve::as<T>{})));
  TTS_EXPECT(eve::all(l.valmin == eve::valmin(eve::as<T>{})));
};

//==================================================================================================
// A scalar EVE recognizes takes the same path as a register, so the two answer the same values.
// Anything EVE does not recognize keeps the built-in set, which is what leaves the specialization
// an addition rather than a replacement.
//==================================================================================================
TTS_CASE("tts::limits agrees between a scalar and its register")
{
  using w_t = eve::wide<float, eve::fixed<4>>;

  auto const s = tts::limits(tts::type<float>{});
  auto const v = tts::limits(tts::type<w_t>{});

  TTS_EXPECT(eve::all(v.valmax == w_t{s.valmax}));
  TTS_EXPECT(eve::all(v.valmin == w_t{s.valmin}));
  TTS_EXPECT(eve::all(v.one    == w_t{s.one}));

  auto const b = tts::limits(tts::type<bool>{});
  TTS_EQUAL(b.valmax, true);
  TTS_EQUAL(b.valmin, false);
};
