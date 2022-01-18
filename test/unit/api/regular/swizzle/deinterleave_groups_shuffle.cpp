//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"

#include <eve/function/deinterleave_groups_shuffle.hpp>

TTS_CASE("Check behavior of deinterleave_groups_shuffle pattern")
{
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 1>), (eve::pattern_t<0>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 2>),
                                                (eve::pattern_t<0, 1>{}));
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<2, 2>),
                                                (eve::pattern_t<0, 1>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 4>),
                      (eve::pattern_t<0, 2, 1, 3>{}));
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<2, 4>),
                      (eve::pattern_t<0, 1, 2, 3>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<1, 8>),
                      (eve::pattern_t<0, 2, 4, 6, 1, 3, 5, 7>{}));
  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<2, 8>),
                      (eve::pattern_t<0, 1, 4, 5, 2, 3, 6, 7>{}));

  TTS_CONSTEXPR_EQUAL((eve::deinterleave_groups_shuffle_pattern<4, 16>),
                      (eve::pattern_t<0, 1, 2, 3,  8,  9, 10, 11,
                                      4, 5, 6, 7, 12, 13, 14, 15>{}));
};

EVE_TEST_TYPES("Check behavior of deinterleave_groups_shuffle size 1, swizzle", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
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

  T res = eve::deinterleave_groups_shuffle(in, eve::lane<1>);

  std::cerr << std::hex << "I : " << in << std::endl;
  std::cerr << std::hex << "E : " << expected << std::endl;
  std::cerr << std::hex << "R : " << res << std::endl;

  TTS_EQUAL(expected, res);
};
