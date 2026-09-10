//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

//==================================================================================================
// tts::limits hands a case the notable values of its type; std::numeric_limits refuses a wide.
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

  TTS_EXPECT(eve::all(eve::is_negative(l.mzero)));
  TTS_EXPECT(eve::all(l.mzero == eve::zero(eve::as<T>{})));
};

//==================================================================================================
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
