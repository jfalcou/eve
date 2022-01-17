//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/deinterleave.hpp>

#include <eve/function/interleave.hpp>

EVE_TEST_TYPES( "Check behavior of interleave on arithmetic data, two registers"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  T field_markers { [](int i, int) { return ((i & 1) ? 0xB : 0xA) << 4; } };

  T a { [](int i, int) { return ( i / 2 ) & 7; }};
  T b { [](int i, int) { return ( i / 2 + T::size() / 2) & 7; }};

  a += field_markers;
  b += field_markers;

  // These inputs are not properly interleaved
  // for 1 element.
  if constexpr (T::size() == 1)
  {
    a = T{0xA0};
    b = T{0xB0};
  }

  T expected_a { [](int i, int) { return 0xA0 | (i & 7); }};
  T expected_b { [](int i, int) { return 0xB0 | (i & 7); }};

  auto [actual_a, actual_b] = eve::deinterleave(a, b);


#if 0
  std::cerr << std::hex << "A : " << a << std::endl;
  std::cerr << std::hex << "B : " << b << std::endl;
  std::cerr << std::hex << "EA: " << expected_a << std::endl;
  std::cerr << std::hex << "RA: " << actual_a << std::endl;
  std::cerr << std::hex << "EB: " << expected_b << std::endl;
  std::cerr << std::hex << "RB: " << actual_b << std::endl;
#endif

  TTS_EQUAL(expected_a, actual_a);
  TTS_EQUAL(expected_b, actual_b);

  // Sanity check

  auto [back_a, back_b] = eve::interleave(expected_a, expected_b);

  TTS_EQUAL(a, back_a);
  TTS_EQUAL(b, back_b);
};

EVE_TEST_TYPES( "Check behavior of interleave on arithmetic data, 3 registers"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  auto field_num = [](int idx) {
    switch (idx % 3)
    {
      case 0 : return 0xA0;
      case 1 : return 0xB0;
      case 2 : return 0xC0;
      default: return 0xF0;
    }
  };

  auto nth_reg = [&](int n) {
    return T([&](int i, int size) {
      i += n * size;
      return field_num(i) | ((i / 3) & 7);
    });
  };

  T a(nth_reg(0));
  T b(nth_reg(1));
  T c(nth_reg(2));

  T expected_a([](int i, int) { return 0xA0 | (i & 0x7); } );
  T expected_b([](int i, int) { return 0xB0 | (i & 0x7); } );
  T expected_c([](int i, int) { return 0xC0 | (i & 0x7); } );

  auto [actual_a, actual_b, actual_c] = eve::deinterleave(a, b, c);

  TTS_EQUAL(expected_a, actual_a);
  TTS_EQUAL(expected_b, actual_b);
  TTS_EQUAL(expected_c, actual_c);

  // Sanity check
  auto [back_a, back_b, back_c] = eve::interleave(expected_a, expected_b, expected_c);

  TTS_EQUAL(a, back_a);
  TTS_EQUAL(b, back_b);
  TTS_EQUAL(c, back_c);
};
