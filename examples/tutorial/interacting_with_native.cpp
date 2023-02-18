//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//! [interating_with_native_algo]

#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>

#include <string>
#include <span>

#ifdef __SSSE3__

void remove_spaces(std::string& s)
{
  using u8x16 = eve::wide<std::uint8_t, eve::fixed<16>>;

  // eve only supports std::int8_t and std::uint8_t, not char.
  std::span s_bytes{reinterpret_cast<std::uint8_t*>(s.data()), s.size()};

  auto end = eve::algo::remove_if[eve::algo::force_cardinal<16>](
    s_bytes,[](u8x16 v) -> eve::logical<u8x16> {
    // A simd is_space we took from @aqrit
    __m128i lut = _mm_setr_epi8(' ',    0,    0,  0,
                                  0,    0,    0,  0,
                                  0, '\t', '\n',  0,
                                  0, '\r',    0,  0);
    return v == u8x16{_mm_shuffle_epi8(lut, v)};
  });

  auto offset = end - s_bytes.begin();
  s.erase(s.begin() + offset, s.end());
}

#endif  // __SSSE3__

//! [interating_with_native_algo]

#include "test.hpp"

TTS_CASE("Check remove spaces") {
#ifdef __SSSE3__
    std::string s = "1   2    3\n  4 \t5";
    remove_spaces(s);
    TTS_EQUAL(s, "12345");
#else
  TTS_PASS();
#endif  // __SSSE3__
};

//! [slicing_aggregate]

TTS_CASE("Slice Example") {
  // Om most platforms is 2 registers or even 4.
  using i32x16 = eve::wide<int, eve::fixed<16>>;

  // half type
  using i32x8  = eve::wide<int, eve::fixed<8>>;

  i32x16 ints {0,  1,   2,   3,
               4,  5,   6,   7,
               8,  9,  10,  11,
               12, 13, 14,  15 };
  i32x8 lo_expected {
    0,  1,   2,   3, 4,  5,   6,   7 };
  i32x8 hi_expected {
    8,  9,  10,  11, 12, 13, 14,  15 };


  TTS_EQUAL(ints.slice(eve::lower_),  lo_expected);
  TTS_EQUAL(ints.slice(eve::upper_), hi_expected);

  auto [lo, hi] = ints.slice();

  TTS_EQUAL(lo, lo_expected);
  TTS_EQUAL(hi, hi_expected);
};

//! [slicing_aggregate]
