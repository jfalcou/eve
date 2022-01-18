//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/deinterleave_shuffle.hpp>

EVE_TEST_TYPES("Check behavior of deinterleave_shuffle swizzle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  std::cout << eve::deinterleave_shuffle_pattern<T::size()> << std::endl;

  T field_markers { [](int i, int) { return ((i & 1) ? 0xB : 0xA) << 4; } };
  T in { [](int i, int) {
    int field_marker = (i & 1) ? 0xB : 0xA;
    return field_marker << 4 | ( (i / 2) & 7);
  }};

  T expected { [](int i, int size) {
    if (i < size / 2 || size == 1) return 0xA0 | (i & 7);
    i -= size / 2;
    return 0xB0 | (i & 7);
  }};

  std::cerr << std::hex << "I : " << in << std::endl;
  std::cerr << std::hex << "E : " << expected << std::endl;
  std::cerr << std::hex << "R : " << eve::deinterleave_shuffle(in) << std::endl;

  TTS_EQUAL(expected, eve::deinterleave_shuffle(in));
};
