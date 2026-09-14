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
// tts::precision measures distances on a wide, a logical and a float16: these pin its four members.
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
  // Not named far: MSVC defines it as an empty macro.
  float const third = std::nextafter(std::nextafter(next, 2.0f), 2.0f);

  w_t const a{one, one, one, one};

  TTS_EQUAL(p<w_t>::ulp(a, a), 0.);

  TTS_EQUAL(p<w_t>::ulp(a, w_t{next, one, one, one}), 0.5);
  TTS_EQUAL(p<w_t>::ulp(a, w_t{next, next, next, next}), 0.5);
  TTS_EQUAL(p<w_t>::ulp(a, w_t{one, one, one, third}), 1.5);

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

  TTS_EQUAL(p<w_t>::ulp(w_t{nan, 1.0}, w_t{nan, 1.0}), 0.);
  TTS_EXPECT(p<w_t>::ulp(n, w_t{1.0, 1.0}) == std::numeric_limits<double>::infinity());
};

//==================================================================================================
TTS_CASE("tts::precision<eve::wide> on integral lanes never leaves the lane type")
{
  using w_t = eve::wide<std::int8_t, eve::fixed<4>>;

  w_t const a{std::int8_t(-83), std::int8_t(0), std::int8_t(0), std::int8_t(0)};
  w_t const b{std::int8_t(-82), std::int8_t(0), std::int8_t(0), std::int8_t(0)};

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

  TTS_EXPECT(p<f_t>::absolute(one, next) < 1e-3);
  TTS_EXPECT(p<f_t>::absolute(one, next) > 0.);

  TTS_EXPECT(p<f_t>::ieee(one, one));
  TTS_EXPECT_NOT(p<f_t>::ieee(one, next));
};
