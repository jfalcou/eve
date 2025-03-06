//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

namespace
{
TTS_CASE_TPL("Check has_equal_in", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr ( std::same_as<T, eve::wide<std::int8_t, eve::fixed<128>>> ) {
    // Overflows
    TTS_PASS();
    return;
  }

  T x {[](int i, int) { return i / 2; }};
  T iota {[](int i, int) { return i; }};

  // basic
  for( int i = 0; i != T::size(); ++i )
  {
    T    m        = iota + i;
    auto expected = x >= i;
    TTS_EQUAL(eve::has_equal_in(x, m), expected) << "x: " << x << "\nm: " << m;
    m = eve::reverse(m);
    TTS_EQUAL(eve::has_equal_in(x, m), expected) << "x: " << x << "\nm: " << m;

    if constexpr( std::signed_integral<eve::element_type_t<T>> )
    {
      m = -m;

      TTS_EQUAL(eve::has_equal_in(x, m, [](auto a, auto b) { return eve::abs(a) == eve::abs(b); }), expected)
          << "x: " << x << "\nm: " << m;
    }
  }
};

TTS_CASE_TPL("Check has_equal_in, different type", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr ( std::same_as<T, eve::wide<std::int8_t, eve::fixed<128>>> ) {
    // Overflows
    TTS_PASS();
    return;
  }

  T x {[](int i, int) { return i - 5; }};

  using L = eve::logical<T>;
  auto p  = [](T reg, L mask) { return reg < 0 && mask; };

  TTS_EXPECT(eve::none(eve::has_equal_in(x, L {false}, p)));

  {
    L expected = x < 0;
    L m {false};
    m.set(0, true);
    L actual = eve::has_equal_in(x, m, p);
    TTS_EQUAL(actual, expected);
  }
};

TTS_CASE_TPL("Check has_equal_in, logical", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using L = eve::logical<T>;
  L x {false};
  L y {true};
  TTS_EXPECT(eve::none(eve::has_equal_in(x, y)));
  y.set(0, false);
  TTS_EXPECT(eve::all(eve::has_equal_in(x, y)));

  TTS_EQUAL(eve::has_equal_in(y, x, eve::logical_xor), y);
};
}
