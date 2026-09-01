//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <cmath>
#include <limits>

//==================================================================================================
// The rest of the suite exercises tts::precision by the side effect of seven hundred files using
// TTS_ULP_EQUAL and friends: none of them checks what the hook returns, so a specialization that
// stopped being selected would only show up as a distance that happens to stay under tolerance.
// These cases pin the four members on the three shapes EVE adds, against values computed by hand.
//
// The negative case — that two different types are rejected — is deliberately absent. It is a
// static_assert inside the function body, which no requires-expression can observe: writing it
// would break this file rather than report a failure.
//==================================================================================================

namespace
{
  template<typename T> using p = tts::precision<T>;
}

//==================================================================================================
TTS_CASE("tts::precision<eve::wide> reports the widest distance over the lanes")
{
  using w_t = eve::wide<float, eve::fixed<4>>;

  float const one  = 1.0f;
  float const next = std::nextafter(one, 2.0f);   // exactly one ULP above
  float const far  = std::nextafter(std::nextafter(next, 2.0f), 2.0f);

  w_t const a{one, one, one, one};

  TTS_EQUAL(p<w_t>::ulp(a, a), 0.);

  // TTS counts a whole ULP as 0.5, and the lane distance is a maximum, not a sum.
  TTS_EQUAL(p<w_t>::ulp(a, w_t{next, one, one, one}), 0.5);
  TTS_EQUAL(p<w_t>::ulp(a, w_t{next, next, next, next}), 0.5);
  TTS_EQUAL(p<w_t>::ulp(a, w_t{one, one, one, far}), 1.5);

  TTS_EQUAL(p<w_t>::absolute(a, a), 0.);
  TTS_EQUAL(p<w_t>::absolute(a, w_t{one, one, one, 4.0f}), 3.);
  TTS_EQUAL(p<w_t>::absolute(a, w_t{1.5f, one, 4.0f, one}), 3.);

  TTS_EQUAL(p<w_t>::relative(a, a), 0.);
  TTS_EQUAL(p<w_t>::relative(a, w_t{2.0f, one, one, one}), 0.5);
};

//==================================================================================================
TTS_CASE("tts::precision<eve::wide>::ieee is the one member that accepts NaN")
{
  using w_t = eve::wide<double, eve::fixed<2>>;

  auto const nan = std::numeric_limits<double>::quiet_NaN();
  auto const inf = std::numeric_limits<double>::infinity();

  w_t const n{nan, 1.0};

  TTS_EXPECT_NOT(eve::all(n == n));
  TTS_EXPECT(p<w_t>::ieee(n, n));
  TTS_EXPECT(p<w_t>::ieee(w_t{inf, inf}, w_t{inf, inf}));
  TTS_EXPECT_NOT(p<w_t>::ieee(n, w_t{1.0, 1.0}));
  TTS_EXPECT_NOT(p<w_t>::ieee(w_t{inf, 1.0}, w_t{-inf, 1.0}));

  // ulp keeps the same convention: two NaNs are at distance zero, a NaN and a number are apart.
  TTS_EQUAL(p<w_t>::ulp(w_t{nan, 1.0}, w_t{nan, 1.0}), 0.);
  TTS_EXPECT(p<w_t>::ulp(n, w_t{1.0, 1.0}) == std::numeric_limits<double>::infinity());
};

//==================================================================================================
TTS_CASE("tts::precision<eve::wide> on integral lanes never leaves the lane type")
{
  using w_t = eve::wide<std::int8_t, eve::fixed<4>>;

  w_t const a{std::int8_t(-83), std::int8_t(0), std::int8_t(0), std::int8_t(0)};
  w_t const b{std::int8_t(-82), std::int8_t(0), std::int8_t(0), std::int8_t(0)};

  // Half a unit apart, as for any integral type. A hook that promoted the lanes to a wider type
  // before measuring would report something else entirely.
  TTS_EQUAL(p<w_t>::ulp(a, b), 0.5);
  TTS_EQUAL(p<w_t>::absolute(a, b), 1.);
};

//==================================================================================================
TTS_CASE_TPL("tts::precision<eve::logical> answers in the two values it has", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  using l_t = eve::logical<T>;

  TTS_EQUAL(p<l_t>::ulp(l_t{true}, l_t{true}), 0.);
  TTS_EQUAL(p<l_t>::ulp(l_t{true}, l_t{false}), std::numeric_limits<double>::infinity());

  TTS_EQUAL(p<l_t>::relative(l_t{false}, l_t{false}), 0.);
  TTS_EQUAL(p<l_t>::relative(l_t{true},  l_t{false}), 1.);

  TTS_EQUAL(p<l_t>::absolute(l_t{false}, l_t{false}), 0.);
  TTS_EQUAL(p<l_t>::absolute(l_t{true},  l_t{false}), 1.);

  TTS_EXPECT(p<l_t>::ieee(l_t{true}, l_t{true}));
  TTS_EXPECT_NOT(p<l_t>::ieee(l_t{true}, l_t{false}));
};

//==================================================================================================
TTS_CASE("tts::precision<eve::float16_t> measures in half precision, not in float")
{
  using f_t = eve::float16_t;

  f_t const one{1};
  f_t const next = eve::next(one);

  TTS_EQUAL(p<f_t>::ulp(one, one), 0.);
  TTS_EQUAL(p<f_t>::ulp(one, next), 0.5);
  TTS_EQUAL(p<f_t>::absolute(one, one), 0.);
  TTS_EQUAL(p<f_t>::relative(one, one), 0.);
  TTS_EQUAL(p<f_t>::relative(f_t{1}, f_t{2}), 0.5);

  // One ULP of float16 is about 9.8e-4. Measured as a float it would be some 8.4e+9 ULP, which is
  // the whole reason this specialization exists.
  TTS_EXPECT(p<f_t>::absolute(one, next) < 1e-3);
  TTS_EXPECT(p<f_t>::absolute(one, next) > 0.);
};
