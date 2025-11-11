//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/regular/shuffle_v2/shuffle_v2_test.hpp"
namespace
{

using eve::na_;

auto return2 = [](auto...) { return 2; };

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1, std::ptrdiff_t... I>
void
run_any_api(eve::pattern_t<I...> p)
{
  shuffle_test::run<T, N, G>(return2, p);
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run_any_api(eve::pattern_formula auto formula)
{
  run_any_api<T, N, G>(eve::fix_pattern<N>(formula));
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run(auto pattern)
{
  if constexpr( eve::current_api >= api ) { run_any_api<T, N, G>(pattern); }
  else { TTS_PASS(); }
}

template <auto api, typename T, std::ptrdiff_t G = 1>
void run_expected_cardinal(auto pattern)
{
  run<api, T, eve::expected_cardinal_v<T>, G>(pattern);
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1, std::ptrdiff_t... I>
void
run2_any_api(eve::pattern_t<I...> p)
{
  shuffle_test::run2<T, N, G>(return2, p);
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run2_any_api(eve::pattern_formula auto formula)
{
  run2_any_api<T, N, G>(eve::fix_pattern<N>(formula));
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run2(auto pattern)
{
  if constexpr( eve::current_api >= api ) { run2_any_api<T, N, G>(pattern); }
  else { TTS_PASS(); }
}

template <auto api, typename T, std::ptrdiff_t G = 1>
void run2_expected_cardinal(auto pattern)
{
  run2<api, T, eve::expected_cardinal_v<T>, G>(pattern);
}

// named common patterns ------------------------------

template <int by>
constexpr auto shift_2_pattern = [](int i, int) {
  return i + by;
};

template <int by>
constexpr auto rotate_pattern = [](int i, int size) {
  return (i + by) % size;
};

constexpr auto reverse_everithing = [](int i, int size) {
  return size - i - 1;
};

template <int g_size>
constexpr auto reverse_in_group = [](int i, int) {
  int group_offset = i / g_size * g_size;
  int in_group = i % g_size;
  return group_offset + g_size - in_group - 1;
};

auto blend_every_other = [](int i, int size)
{
  if( i % 2 ) return i + size;
  return i;
};


// any api --------------------------------------------

TTS_CASE("int <<, >>")
{
  run_any_api<std::uint8_t, 2>(eve::pattern<1, na_>);
  run_any_api<std::uint8_t, 4>(eve::pattern<1, 2, 3, na_>);
  run_any_api<std::uint8_t, 8>(eve::pattern<1, 2, 3, na_, 5, 6, 7, na_>);
  run_any_api<std::uint8_t, 16>(
      eve::pattern<1, 2, 3, na_, 5, 6, 7, na_, 9, 10, 11, na_, 13, 14, 15, na_>);
  run_any_api<std::uint8_t, 4>(eve::pattern<2, 3, na_, na_>);
  run_any_api<std::uint8_t, 8>(eve::pattern<2, 3, na_, na_, 6, 7, na_, na_>);
  run_any_api<std::uint8_t, 4>(eve::pattern<3, na_, na_, na_>);
  run_any_api<std::uint8_t, 8>(eve::pattern<5, 6, 7, na_, na_, na_, na_, na_>);

  run_any_api<std::uint8_t, 2>(eve::pattern<na_, 0>);
  run_any_api<std::uint8_t, 4>(eve::pattern<na_, 0, 1, 2>);
  run_any_api<std::uint8_t, 8>(eve::pattern<na_, 0, 1, 2, na_, 4, 5, 6>);
  run_any_api<std::uint8_t, 16>(
      eve::pattern<na_, 0, 1, 2, na_, 4, 5, 6, na_, 8, 9, 10, na_, 12, 13, 14>);
  run_any_api<std::uint8_t, 4>(eve::pattern<na_, na_, 0, 1>);
  run_any_api<std::uint8_t, 4>(eve::pattern<na_, na_, na_, 0>);
  run_any_api<std::uint8_t, 8>(eve::pattern<na_, na_, na_, na_, na_, 0, 1, 2>);
};

// x86 ------------------------------------------------

TTS_CASE("_mm_bsrli_si128/_mm_bslli_si128")
{
  run<eve::sse2, std::uint8_t, 16>(
      [](std::ptrdiff_t i, std::ptrdiff_t size)
      {
        if( i + 3 >= size ) return eve::na_;
        return i + 3;
      });
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<5, 6, 7, na_, na_, na_, na_, na_>);
  run<eve::sse2, std::uint32_t, 4>(eve::pattern<1, 2, 3, na_>);
  run<eve::sse2, std::uint64_t, 2>(eve::pattern<1, na_>);

  run<eve::sse2, std::uint8_t, 16>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( i < 3 ) return eve::na_;
        return i - 3;
      });
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<na_, na_, na_, na_, na_, 0, 1, 2>);
  run<eve::sse2, std::uint32_t, 4>(eve::pattern<na_, 0, 1, 2>);
  run<eve::sse2, std::uint64_t, 2>(eve::pattern<na_, 0>);

  run<eve::avx2, std::uint8_t, 32>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 <= i && i < 15 ) return i + 1;
        if( 16 <= i && i < 31 ) return i + 1;
        return na_;
      });
  run<eve::avx2, std::uint16_t, 16>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 <= i && i < 7 ) return i + 1;
        if( 8 <= i && i < 15 ) return i + 1;
        return na_;
      });

  run<eve::avx2, std::uint32_t, 8>(eve::pattern<1, 2, 3, na_, 5, 6, 7, na_>);
  run<eve::avx2, std::uint64_t, 4>(eve::pattern<1, na_, 3, na_>);

  run<eve::avx2, std::uint8_t, 32>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 < i && i <= 15 ) return i - 1;
        if( 16 < i && i <= 31 ) return i - 1;
        return na_;
      });
  run<eve::avx2, std::uint16_t, 16>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 < i && i <= 7 ) return i - 1;
        if( 8 < i && i <= 15 ) return i - 1;
        return na_;
      });

  run<eve::avx2, std::uint32_t, 8>(eve::pattern<na_, 0, 1, 2, na_, 4, 5, 6>);
  run<eve::avx2, std::uint64_t, 4>(eve::pattern<na_, 0, na_, 2>);

  run<eve::avx512, std::uint8_t, 64>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 <= i && i < 15 ) return i + 1;
        if( 16 <= i && i < 31 ) return i + 1;
        if( 32 <= i && i < 47 ) return i + 1;
        if( 48 <= i && i < 63 ) return i + 1;
        return na_;
      });
  run<eve::avx512, std::uint16_t, 32>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 <= i && i < 7 ) return i + 1;
        if( 8 <= i && i < 15 ) return i + 1;
        if( 16 <= i && i < 23 ) return i + 1;
        if( 24 <= i && i < 31 ) return i + 1;
        return na_;
      });

  run<eve::avx512, std::uint8_t, 64>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 < i && i <= 15 ) return i - 1;
        if( 16 < i && i <= 31 ) return i - 1;
        if( 32 < i && i <= 47 ) return i - 1;
        if( 48 < i && i <= 63 ) return i - 1;
        return na_;
      });
  run<eve::avx512, std::uint16_t, 32>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( 0 < i && i <= 7 ) return i - 1;
        if( 8 < i && i <= 15 ) return i - 1;
        if( 16 < i && i <= 23 ) return i - 1;
        if( 24 < i && i <= 31 ) return i - 1;
        return na_;
      });
};

TTS_CASE("_mm_shufflelo_epi16/_mm_shufflehi_epi16")
{
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<1, 2, 3, 0, /**/ 4, 5, 6, 7>);
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<0, 2, 2, 0, /**/ 4, 5, 6, 7>);
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<2, 3, 1, 0, /**/ 4, 5, 6, 7>);
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<0, 3, 3, 2, /**/ 4, 5, 6, 7>);

  run<eve::sse2, std::uint16_t, 8>(eve::pattern<0, 1, 2, 3, /**/ 5, 6, 7, 4>);
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<0, 1, 2, 3, /**/ 4, 5, 5, 4>);
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<0, 1, 2, 3, /**/ 4, 6, 6, 5>);
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<0, 1, 2, 3, /**/ 7, 6, 7, 6>);

  run<eve::avx2, std::uint16_t, 16>(eve::pattern<
                                    // clang-format off
      1, 2,  3,  0, /**/  4,  5,  6, 7, /**/
      9, 10, 11, 8, /**/ 12, 13, 14, 15>
                                    // clang-format on
  );
  run<eve::avx2, std::uint16_t, 16>(eve::pattern<
                                    // clang-format off
      0, 1,  2,  3, /**/  4,  6,  7, 5, /**/
      8, 9, 10, 11, /**/ 12, 14, 15, 13>
                                    // clang-format on
  );

  run<eve::avx512, std::uint16_t, 32>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( i % 8 == 0 ) return i + 1;
        if( i % 8 == 1 ) return i + 2;
        if( i % 8 == 2 ) return i - 1;
        if( i % 8 == 3 ) return i - 3;
        return i;
      });
  run<eve::avx512, std::uint16_t, 32>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        if( i % 8 == 4 ) return i + 1;
        if( i % 8 == 5 ) return i + 2;
        if( i % 8 == 6 ) return i - 1;
        if( i % 8 == 7 ) return i - 3;
        return i;
      });
};

TTS_CASE("_mm_shuffle_epi32/_mm_permute_ps")
{
  run<eve::sse2, std::uint32_t, 4>(eve::pattern<3, 0, 1, 2>);
  run<eve::sse2, std::uint32_t, 4>(eve::pattern<2, 2, 3, 1>);

  run<eve::avx, std::uint32_t, 8>(eve::pattern<3, 0, 1, 2, 7, 4, 5, 6>);
  run<eve::avx, std::uint32_t, 8>(eve::pattern<2, 2, 3, 1, 6, 6, 7, 5>);

  run<eve::avx512, std::uint32_t, 16>(
      [](int i, int)
      {
        if( i % 4 == 0 ) return i + 3;
        if( i % 4 == 1 ) return i - 1;
        if( i % 4 == 2 ) return i + 1;
        if( i % 4 == 3 ) return i - 3;
        return i;
      });
};

TTS_CASE("_mm_alignr_epi8(x, x)")
{
  run<eve::ssse3, std::uint8_t, 16>(
      eve::pattern<1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0>);
  run<eve::ssse3, std::uint16_t, 8>(eve::pattern<1, 2, 3, 4, 5, 6, 7, 0>);
  run<eve::ssse3, std::uint8_t, 16>(
      eve::pattern<3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2>);

  run<eve::avx2, std::uint8_t, 32>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        std::ptrdiff_t part   = i / 16 * 16;
        std::ptrdiff_t offset = i % 16;
        return part + (offset + 3) % 16;
      });

  run<eve::avx512, std::uint8_t, 64>(
      [](std::ptrdiff_t i, std::ptrdiff_t)
      {
        std::ptrdiff_t part   = i / 16 * 16;
        std::ptrdiff_t offset = i % 16;
        return part + (offset + 3) % 16;
      });
};

TTS_CASE("_mm_move_epi64 / _mm_insert_epi16")
{
  run<eve::sse4_1, std::uint64_t, 2>(eve::pattern<na_, 1>);
  run<eve::sse2, std::uint64_t, 2>(eve::pattern<0, na_>);

  run<eve::sse2, std::uint16_t, 8>(eve::pattern<na_, 1, 2, 3, 4, 5, 6, 7>);
  run<eve::sse2, std::uint16_t, 8>(eve::pattern<0, 1, 2, 3, 4, 5, na_, 7>);

  run<eve::sse4_1, std::uint32_t, 4>(eve::pattern<na_, 1, 2, 3>);
  run<eve::sse4_1, std::uint32_t, 4>(eve::pattern<0, na_, 2, 3>);
  run<eve::sse4_1, std::uint32_t, 4>(eve::pattern<0, 1, na_, 3>);
  run<eve::sse4_1, std::uint32_t, 4>(eve::pattern<0, 1, 2, na_>);

  run<eve::sse4_1, std::uint8_t, 16>([](std::ptrdiff_t i, std::ptrdiff_t)
                                     { return (i == 0) ? na_ : i; });
  run<eve::sse4_1, std::uint8_t, 16>([](std::ptrdiff_t i, std::ptrdiff_t)
                                     { return (i == 5) ? na_ : i; });
};

TTS_CASE("_mm_permute_pd")
{
  // At the time of writing these are not actually implemented as
  // _mm_permute_pd but _mm_permute_pd could do them so we
  // test that we are getting a level 2 shuffle here.
  //
  // _mm_permute_pd is just worse than _mm_shuffle_epi32 for example
  run<eve::avx, std::uint64_t, 2>(eve::pattern<0, 0>);
  run<eve::avx, std::uint64_t, 2>(eve::pattern<1, 1>);
  run<eve::avx, std::uint64_t, 2>(eve::pattern<1, 0>);

  run<eve::avx, std::uint64_t, 4>(eve::pattern<1, 0, 3, 2>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<1, 0, 2, 3>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<0, 0, 2, 2>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<0, 0, 3, 3>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<1, 0, 2, 3>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<1, 1, 2, 2>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<1, 1, 3, 3>);

  run<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 0, 2, 2, /**/ 4, 4, 6, 6>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 0, 3, 3, /**/ 4, 4, 7, 7>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 0, 3, 3, /**/ 5, 5, 6, 6>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<1, 0, 3, 2, /**/ 4, 5, 6, 6>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<1, 1, 2, 2, /**/ 5, 4, 7, 6>);
};

TTS_CASE("_mm_permute4x64_epi64 / _mm_permutex_epi64")
{
  run<eve::avx2, std::uint64_t, 4>(eve::pattern<1, 0, 3, 2>);
  run<eve::avx2, std::uint64_t, 4>(eve::pattern<3, 0, 2, 3>);
  run<eve::avx2, std::uint64_t, 4>(eve::pattern<1, 1, 3, 3>);
  run<eve::avx2, std::uint64_t, 4>(eve::pattern<1, 1, 1, 1>);
  run<eve::avx2, std::uint64_t, 4>(eve::pattern<3, 2, 1, 0>);

  run<eve::avx2, std::uint64_t, 8>(eve::pattern<1, 0, 3, 2, /**/ 5, 4, 7, 6>);
  run<eve::avx2, std::uint64_t, 8>(eve::pattern<3, 0, 2, 3, /**/ 7, 4, 6, 7>);
  run<eve::avx2, std::uint64_t, 8>(eve::pattern<2, 2, 2, 2, /**/ 6, 6, 6, 6>);
  run<eve::avx2, std::uint64_t, 8>(eve::pattern<0, 1, 1, 0, /**/ 4, 5, 5, 4>);
};

TTS_CASE("_mm_permute2f128_si256")
{
  run<eve::avx, std::uint64_t, 4>(eve::pattern<0, 1, 0, 1>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<2, 3, 2, 3>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<2, 3, na_, na_>);
  run<eve::avx, std::uint64_t, 4>(eve::pattern<na_, na_, 2, 3>);
};

TTS_CASE("_mm_shuffle_i64x2")
{
  // one register
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 1, 0, 1, 0, 1, 0, 1>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<6, 7, 4, 5, 2, 3, 0, 1>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<6, 7, 2, 3, 2, 3, 0, 1>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<2, 3, 6, 7, 2, 3, 4, 5>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<4, 5, 0, 1, 6, 7, 2, 3>);
};

TTS_CASE("_mm_alignr_epi32(x, x) / _mm_alignr_epi64(x, x)")
{
  // NOTE: _mm_alignr_epi32 / _mm_alignr_epi64 are not generated,
  //       _mm_alignr_epi8 is better.
  //
  //       _mm256_alignr_epi64 is never generated at the moment,
  //       _mm256_permute4x64_epi64 is used instead.
  //       They are equivalent.
  run<eve::avx512, std::uint32_t, 4>(eve::pattern<1, 2, 3, 0>);
  run<eve::avx512, std::uint32_t, 4>(eve::pattern<2, 3, 0, 1>);
  run<eve::avx512, std::uint32_t, 4>(eve::pattern<3, 0, 1, 2>);

  run<eve::avx512, std::uint32_t, 8>(eve::pattern<1, 2, 3, 4, 5, 6, 7, 0>);
  run<eve::avx512, std::uint32_t, 8>(eve::pattern<2, 3, 4, 5, 6, 7, 0, 1>);
  run<eve::avx512, std::uint32_t, 8>(eve::pattern<3, 4, 5, 6, 7, 0, 1, 2>);
  run<eve::avx512, std::uint32_t, 8>(eve::pattern<4, 5, 6, 7, 0, 1, 2, 3>);

  run<eve::avx512, std::uint64_t, 8>(eve::pattern<1, 2, 3, 4, 5, 6, 7, 0>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<2, 3, 4, 5, 6, 7, 0, 1>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<3, 4, 5, 6, 7, 0, 1, 2>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<4, 5, 6, 7, 0, 1, 2, 3>);

  run<eve::avx512, std::uint32_t, 16>([](int i, int size) { return (i + 1) % size; });
  run<eve::avx512, std::uint32_t, 16>([](int i, int size) { return (i + 3) % size; });
  run<eve::avx512, std::uint32_t, 16>([](int i, int size) { return (i + 5) % size; });
  run<eve::avx512, std::uint32_t, 16>([](int i, int size) { return (i + 7) % size; });
  run<eve::avx512, std::uint32_t, 16>([](int i, int size) { return (i + 9) % size; });
  run<eve::avx512, std::uint32_t, 16>([](int i, int size) { return (i + 11) % size; });
};

TTS_CASE("_mm_blend_ps / _mm_blend_pd / _mm_mask_blend")
{
  run2<eve::sse4_1, std::uint32_t, 4>(eve::pattern<0, 1, 2, 7>);
  run2<eve::sse4_1, std::uint32_t, 4>(eve::pattern<0, 5, 2, 7>);
  run2<eve::sse4_1, std::uint32_t, 4>(eve::pattern<4, 5, 2, 7>);

  run2<eve::avx512, std::uint8_t, 16>(blend_every_other);
  run2<eve::avx512, std::uint16_t, 8>(blend_every_other);
  run2<eve::sse4_1, std::uint32_t, 4>(blend_every_other);
  run2<eve::sse4_1, std::uint64_t, 2>(blend_every_other);

  run2<eve::avx512, std::uint8_t, 32>(blend_every_other);
  run2<eve::avx512, std::uint16_t, 16>(blend_every_other);
  run2<eve::avx, std::uint32_t, 8>(blend_every_other);
  run2<eve::avx, std::uint64_t, 4>(blend_every_other);

  run2<eve::avx512, std::uint8_t, 64>(blend_every_other);
  run2<eve::avx512, std::uint16_t, 32>(blend_every_other);
  run2<eve::avx512, std::uint32_t, 16>(blend_every_other);
  run2<eve::avx512, std::uint64_t, 8>(blend_every_other);
};

template <int alignment>
constexpr auto alignr_epi8_pattern = [] (int i, int size) {
  int lane = i / 16;
  int offset = i % 16;

  int offset2 = offset + alignment;
  if (offset2 >= 16) {
    offset2 %= 16;
    offset2 += size;
  }

  return lane * 16 + offset2;
};

TTS_CASE("_mm_alignr_epi8(x, y)")
{
  run2<eve::ssse3, std::uint8_t, 16>(alignr_epi8_pattern<1>);
  run2<eve::ssse3, std::uint8_t, 16>(alignr_epi8_pattern<2>);
  run2<eve::ssse3, std::uint8_t, 16>(alignr_epi8_pattern<3>);
  run2<eve::ssse3, std::uint8_t, 16>(alignr_epi8_pattern<5>);
  run2<eve::ssse3, std::uint8_t, 16>(alignr_epi8_pattern<9>);
  run2<eve::ssse3, std::uint8_t, 16>(alignr_epi8_pattern<13>);

  run2<eve::avx2, std::uint8_t, 32>(alignr_epi8_pattern<1>);
  run2<eve::avx2, std::uint8_t, 32>(alignr_epi8_pattern<2>);
  run2<eve::avx2, std::uint8_t, 32>(alignr_epi8_pattern<3>);
  run2<eve::avx2, std::uint8_t, 32>(alignr_epi8_pattern<5>);
  run2<eve::avx2, std::uint8_t, 32>(alignr_epi8_pattern<9>);
  run2<eve::avx2, std::uint8_t, 32>(alignr_epi8_pattern<13>);

  run2<eve::avx512, std::uint8_t, 64>(alignr_epi8_pattern<1>);
  run2<eve::avx512, std::uint8_t, 64>(alignr_epi8_pattern<2>);
  run2<eve::avx512, std::uint8_t, 64>(alignr_epi8_pattern<3>);
  run2<eve::avx512, std::uint8_t, 64>(alignr_epi8_pattern<5>);
  run2<eve::avx512, std::uint8_t, 64>(alignr_epi8_pattern<9>);
  run2<eve::avx512, std::uint8_t, 64>(alignr_epi8_pattern<13>);
};

TTS_CASE("_mm_shuffle_ps(x, y)")
{
  run2<eve::sse2, std::uint32_t, 4>(eve::pattern<0, 2, 4, 5>);
  run2<eve::sse2, std::uint32_t, 4>(eve::pattern<1, 0, 4, 5>);

  auto p0 = [](int i, int size) {
    if (i % 4 == 0) return i + 1;
    if (i % 4 == 1) return i - 1;
    if (i % 4 == 2) return i + 1 + size;
    /*if (i % 4 == 3)*/ return i - 1 + size;
  };

  auto p1 = [](int i, int size) {
    if (i % 4 == 0) return i + 2;
    if (i % 4 == 1) return i + 2;
    if (i % 4 == 2) return i - 2 + size;
    /*if (i % 4 == 3)*/ return i - 2 + size;
  };

  auto p2 = [](int i, int size) {
    if (i % 4 == 0) return i + 2;
    if (i % 4 == 1) return i + 2;
    if (i % 4 == 2) return i + size;
    /*if (i % 4 == 3)*/ return i + size;
  };

  auto p3 = [](int i, int size) {
    if (i % 4 == 0) return i + 1;
    if (i % 4 == 1) return i;
    if (i % 4 == 2) return i + size;
    /*if (i % 4 == 3)*/ return i + size;
  };


  run2<eve::sse2, std::uint32_t, 4>(p0);
  run2<eve::sse2, std::uint32_t, 4>(p1);
  run2<eve::sse2, std::uint32_t, 4>(p2);
  run2<eve::sse2, std::uint32_t, 4>(p3);

  run2<eve::avx, std::uint32_t, 8>(p0);
  run2<eve::avx, std::uint32_t, 8>(p1);
  run2<eve::avx, std::uint32_t, 8>(p2);
  run2<eve::avx, std::uint32_t, 8>(p3);

  run2<eve::avx512, std::uint32_t, 16>(p0);
  run2<eve::avx512, std::uint32_t, 16>(p1);
  run2<eve::avx512, std::uint32_t, 16>(p2);
  run2<eve::avx512, std::uint32_t, 16>(p3);
};

TTS_CASE("_mm_shuffle_pd(x, y)")
{
  // avx2:   [0, 1, 2, 3][4, 5, 6, 7]
  // avx512: [0, 1, 2, 3, 4, 5, 6, 7] [8, 9, 10, 11, 12, 13, 14, 15]

  // These are repeated patterns so they happen to be covered by shuffle_ps.
  run2<eve::sse2, std::uint64_t, 2>(eve::pattern<0, 2>);
  run2<eve::sse2, std::uint64_t, 2>(eve::pattern<1, 2>);
  run2<eve::sse2, std::uint64_t, 2>(eve::pattern<0, 3>);
  run2<eve::sse2, std::uint64_t, 2>(eve::pattern<1, 3>);

  run2<eve::avx, std::uint64_t, 4>(eve::pattern<0, 5, 2, 7>);
  run2<eve::avx, std::uint64_t, 4>(eve::pattern<1, 5, 3, 7>);

  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 8, 2, 10, 4, 12, 6, 14>);
  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<1, 8, 3, 10, 5, 12, 7, 14>);
  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 9, 2, 11, 4, 13, 6, 15>);
  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<1, 9, 3, 11, 5, 13, 7, 15>);

  // These should proper trigger shuffle_pd

  run2<eve::avx, std::uint64_t, 4>(eve::pattern<0, 4, 2, 7>);
  run2<eve::avx, std::uint64_t, 4>(eve::pattern<1, 4, 2, 7>);
  run2<eve::avx, std::uint64_t, 4>(eve::pattern<1, 5, 3, 7>);
  run2<eve::avx, std::uint64_t, 4>(eve::pattern<1, 4, 3, 7>);
  run2<eve::avx, std::uint64_t, 4>(eve::pattern<1, 5, 2, 6>);
  run2<eve::avx, std::uint64_t, 4>(eve::pattern<0, 5, 3, 6>);

  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<1, 8, 2, 10, 4, 12, 6, 14>);
  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<1, 8, 2, 11, 4, 12, 6, 15>);
  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 9, 2, 10, 5, 13, 6, 15>);
  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 8, 3, 10, 4, 13, 7, 14>);
};

TTS_CASE("_mm_permute2f128_si256(x, y) / _mm_shuffle_i64x2(x, y)")
{
  // [0, 1] [2, 3]
  run2<eve::avx, std::uint64_t, 4, /*G*/ 2>(eve::pattern<0, 2>);
  run2<eve::avx, std::uint64_t, 4, /*G*/ 2>(eve::pattern<1, 2>);
  run2<eve::avx, std::uint64_t, 4, /*G*/ 2>(eve::pattern<0, 3>);
  run2<eve::avx, std::uint64_t, 4, /*G*/ 2>(eve::pattern<1, 3>);

  // [0, 1, 2, 3][4, 5, 6, 7] -> first half from x, second half is from y
  run2<eve::avx512, std::uint64_t, 8, /*G*/ 2>(eve::pattern<0, 0, 4, 5>);
  run2<eve::avx512, std::uint64_t, 8, /*G*/ 2>(eve::pattern<2, 2, 4, 5>);
  run2<eve::avx512, std::uint64_t, 8, /*G*/ 2>(eve::pattern<1, 2, 7, 4>);
  run2<eve::avx512, std::uint64_t, 8, /*G*/ 2>(eve::pattern<3, 0, 6, 5>);
  run2<eve::avx512, std::uint64_t, 8, /*G*/ 2>(eve::pattern<3, 1, 5, 6>);
};

TTS_CASE("_mm_alignr_epi32(x, y), _mm_alignr_epi64(x, y)")
{
  // [0, 1, 2, 3][4, 5, 6, 7]
  run2<eve::avx512, std::uint32_t, 4>(eve::pattern<1, 2, 3, 4>);
  run2<eve::avx512, std::uint32_t, 4>(eve::pattern<2, 3, 4, 5>);
  run2<eve::avx512, std::uint32_t, 4>(eve::pattern<3, 4, 5, 6>);

  run2<eve::avx512, std::uint32_t, 8>(shift_2_pattern<1>);
  run2<eve::avx512, std::uint32_t, 8>(shift_2_pattern<2>);
  run2<eve::avx512, std::uint32_t, 8>(shift_2_pattern<3>);
  run2<eve::avx512, std::uint32_t, 8>(shift_2_pattern<4>);
  run2<eve::avx512, std::uint32_t, 8>(shift_2_pattern<5>);
  run2<eve::avx512, std::uint32_t, 8>(shift_2_pattern<6>);
  run2<eve::avx512, std::uint32_t, 8>(shift_2_pattern<7>);

  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<1>);
  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<2>);
  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<4>);
  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<7>);
  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<8>);
  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<9>);
  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<14>);
  run2<eve::avx512, std::uint32_t, 16>(shift_2_pattern<15>);
};

// arm-neon -------------------------------------------

TTS_CASE("vext(x, x)")
{
  run<eve::neon, std::uint8_t, 8>(rotate_pattern<1>);
  run<eve::neon, std::uint8_t, 8>(rotate_pattern<2>);
  run<eve::neon, std::uint8_t, 8>(rotate_pattern<3>);
  run<eve::neon, std::uint8_t, 8>(rotate_pattern<4>);

  run<eve::neon, std::uint8_t, 16>(rotate_pattern<1>);
  run<eve::neon, std::uint8_t, 16>(rotate_pattern<2>);
  run<eve::neon, std::uint8_t, 16>(rotate_pattern<3>);
  run<eve::neon, std::uint8_t, 16>(rotate_pattern<4>);
  run<eve::neon, std::uint8_t, 16>(rotate_pattern<7>);
  run<eve::neon, std::uint8_t, 16>(rotate_pattern<8>);

  run<eve::neon, std::uint32_t, 4>(eve::pattern<3, 0, 1, 2>);
  run<eve::neon, std::uint64_t, 2>(eve::pattern<1, 0>);
};

TTS_CASE("vcopy_lane(x, x)")
{
  run<eve::asimd, std::uint8_t, 8>(eve::pattern<0, 4, 2, 3, 4, 5, 6, 7>);
  run<eve::asimd, std::uint8_t, 16>([](int i, int) { return (i == 7) ? 2 : i; });

  run<eve::asimd, std::uint16_t, 4>(eve::pattern<3, 1, 2, 3>);
  run<eve::asimd, std::uint16_t, 8>(eve::pattern<0, 1, 2, 3, 4, 5, 5, 7>);

  run<eve::asimd, std::uint32_t, 2>(eve::pattern<1, 1>);
  run<eve::asimd, std::uint32_t, 4>(eve::pattern<2, 1, 2, 3>);

  run<eve::asimd, std::uint64_t, 2>(eve::pattern<1, 1>);
};

TTS_CASE("vset_lane(0)")
{
  run<eve::neon, std::uint8_t, 8>(eve::pattern<0, 1, 2, 3, 4, na_, 6, 7>);
  run<eve::neon, std::uint8_t, 16>([](int i, int) { return (i == 4) ? na_ : i; });

  run<eve::neon, std::uint16_t, 4>(eve::pattern<0, 1, 2, na_>);
  run<eve::neon, std::uint16_t, 8>(eve::pattern<0, 1, 2, 3, 4, 5, na_, 7>);

  run<eve::neon, std::uint32_t, 2>(eve::pattern<0, na_>);
  run<eve::neon, std::uint32_t, 4>(eve::pattern<na_, 1, 2, 3>);

  run<eve::neon, std::uint64_t, 2>(eve::pattern<na_, 1>);
};

TTS_CASE("vrev")
{
  // 8 bytes
  run<eve::neon, std::uint8_t, 8>(eve::pattern<7, 6, 5, 4, 3, 2, 1, 0>);
  run<eve::neon, std::uint8_t, 8>(eve::pattern<3, 2, 1, 0, 7, 6, 5, 4>);
  run<eve::neon, std::uint8_t, 8>(eve::pattern<1, 0, 3, 2, 5, 4, 7, 6>);

  run<eve::neon, std::uint16_t, 4>(eve::pattern<3, 2, 1, 0>);
  run<eve::neon, std::uint16_t, 4>(eve::pattern<1, 0, 3, 2>);

  run<eve::neon, std::uint32_t, 2>(eve::pattern<1, 0>);

  // 16 bytes
  // clang-format off
  run<eve::neon, std::uint8_t, 16>(eve::pattern< //
    7, 6, 5, 4, 3, 2, 1, 0, //
    15, 14, 13, 12, 11, 10, 9, 8 //
  >);
  run<eve::neon, std::uint8_t, 16>(eve::pattern< //
    3, 2, 1, 0,    //
    7, 6, 5, 4,    //
    11, 10, 9, 8,  //
    15, 14, 13, 12 //
  >);
  run<eve::neon, std::uint8_t, 16>(eve::pattern< //
    1, 0, 3, 2,    //
    5, 4, 7, 6,    //
    9, 8, 11, 10,  //
    13, 12, 15, 14 //
  >);
  // clang-format on

  run<eve::neon, std::uint16_t, 8>(eve::pattern<3, 2, 1, 0, 7, 6, 5, 4>);
  run<eve::neon, std::uint16_t, 8>(eve::pattern<1, 0, 3, 2, 5, 4, 7, 6>);

  run<eve::neon, std::uint32_t, 4>(eve::pattern<1, 0, 3, 2>);
};

TTS_CASE("vdup_lane")
{
  run<eve::neon, std::uint8_t, 8>(eve::pattern<0, 0, 0, 0, 0, 0, 0, 0>);
  run<eve::neon, std::uint8_t, 8>(eve::pattern<5, 5, 5, 5, 5, 5, 5, 5>);
  run<eve::asimd, std::uint8_t, 16>([](int, int) { return 3; });

  run<eve::neon, std::uint16_t, 4>(eve::pattern<1, 1, 1, 1>);
  run<eve::asimd, std::uint16_t, 8>(eve::pattern<2, 2, 2, 2, 2, 2, 2, 2>);

  run<eve::neon, std::uint32_t, 2>(eve::pattern<1, 1>);
  run<eve::asimd, std::uint32_t, 4>(eve::pattern<3, 3, 3, 3>);

  run<eve::asimd, std::uint64_t, 2>(eve::pattern<1, 1>);
};

TTS_CASE("vcopy_lane(x, y)")
{
  run2<eve::asimd, std::uint8_t, 8>(eve::pattern<0, 1, 2, 3, 4, 13, 6, 7>);
  run2<eve::asimd, std::uint8_t, 16>([](int i, int size) { return (i == 2) ? i + size : i; });

  run2<eve::asimd, std::uint16_t, 4>(eve::pattern<0, 1, 2, 7>);
  run2<eve::asimd, std::uint16_t, 8>(eve::pattern<0, 9, 2, 3, 4, 5, 6, 7>);

  run2<eve::asimd, std::uint32_t, 2>(eve::pattern<0, 3>);
  run2<eve::asimd, std::uint32_t, 4>(eve::pattern<4, 1, 2, 3>);

  run2<eve::asimd, std::uint64_t, 2>(eve::pattern<2, 1>);
};

TTS_CASE("vext(x, y)")
{
  run2<eve::neon, std::uint8_t, 8>(shift_2_pattern<1>);
  run2<eve::neon, std::uint8_t, 8>(shift_2_pattern<2>);
  run2<eve::neon, std::uint8_t, 8>(shift_2_pattern<3>);
  run2<eve::neon, std::uint8_t, 8>(shift_2_pattern<4>);
  run2<eve::neon, std::uint8_t, 8>(shift_2_pattern<5>);
  run2<eve::neon, std::uint8_t, 8>(shift_2_pattern<6>);
  run2<eve::neon, std::uint8_t, 8>(shift_2_pattern<7>);

  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<1>);
  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<2>);
  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<3>);
  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<4>);
  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<5>);
  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<8>);
  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<13>);
  run2<eve::neon, std::uint8_t, 16>(shift_2_pattern<14>);
};

// arm-sve --------------------------------------------

TTS_CASE("svdup_lane")
{
  run_expected_cardinal<eve::sve, std::uint8_t>([](int, int) { return 3; });
  run_expected_cardinal<eve::sve, std::uint8_t>([](int, int size) { return size - 5; });

  run_expected_cardinal<eve::sve, std::uint16_t>([](int, int) { return 2; });
  run_expected_cardinal<eve::sve, std::uint16_t>([](int, int size) { return size - 1; });

  run_expected_cardinal<eve::sve, std::uint32_t>([](int, int) { return 0; });
  run_expected_cardinal<eve::sve, std::uint32_t>([](int, int size) { return size - 4; });

  run_expected_cardinal<eve::sve, std::uint64_t>([](int, int) { return 1; });
  run_expected_cardinal<eve::sve, std::uint64_t>([](int, int size) { return size - 1; });
};

TTS_CASE("svrev/svrev_b")
{
  run_expected_cardinal<eve::sve, std::uint8_t>(reverse_everithing);
  run_expected_cardinal<eve::sve, eve::logical<std::uint8_t>>(reverse_everithing);

  run_expected_cardinal<eve::sve, std::uint16_t>(reverse_everithing);
  run_expected_cardinal<eve::sve, eve::logical<std::uint16_t>>(reverse_everithing);

  run_expected_cardinal<eve::sve, std::uint32_t>(reverse_everithing);
  run_expected_cardinal<eve::sve, eve::logical<std::uint32_t>>(reverse_everithing);

  run_expected_cardinal<eve::sve, std::uint64_t>(reverse_everithing);
  run_expected_cardinal<eve::sve, eve::logical<std::uint64_t>>(reverse_everithing);
};

TTS_CASE("svrevb/svrevh/svrevw")
{
  run_expected_cardinal<eve::sve, std::uint8_t>(reverse_in_group<8>);
  run_expected_cardinal<eve::sve, std::uint8_t>(reverse_in_group<4>);
  run_expected_cardinal<eve::sve, std::uint8_t>(reverse_in_group<2>);

  run_expected_cardinal<eve::sve, std::uint16_t>(reverse_in_group<4>);
  run_expected_cardinal<eve::sve, std::uint16_t>(reverse_in_group<2>);

  run_expected_cardinal<eve::sve, std::uint32_t>(reverse_in_group<2>);
};

TTS_CASE("svext(x, x)")
{
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<1>);
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<2>);
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<3>);
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<4>);
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<7>);
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<8>);

  constexpr int size = eve::expected_cardinal_v<std::uint8_t>;
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<size - 3>);
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<size / 2>);
  run_expected_cardinal<eve::sve, std::uint8_t>(rotate_pattern<size - size / 4>);
};

TTS_CASE("svsel")
{
  run2_expected_cardinal<eve::sve, std::uint8_t>(blend_every_other);
  run2_expected_cardinal<eve::sve, std::uint16_t>(blend_every_other);
  run2_expected_cardinal<eve::sve, std::uint32_t>(blend_every_other);
  run2_expected_cardinal<eve::sve, std::uint64_t>(blend_every_other);
};

TTS_CASE("svext(x, y)")
{
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<1>);
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<2>);
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<3>);
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<4>);
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<8>);
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<9>);

  constexpr int size = eve::expected_cardinal_v<std::uint8_t>;
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<size - 3>);
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<size / 2>);
  run2_expected_cardinal<eve::sve, std::uint8_t>(shift_2_pattern<size - size / 4>);
};

// power-pc -------------------------------------------

TTS_CASE("vec_splat")
{
  run<eve::vmx, std::uint8_t, 16>([](int, int) { return 3; });
  run<eve::vmx, std::uint16_t, 8>([](int, int) { return 4; });
  run<eve::vmx, std::uint32_t, 4>([](int, int) { return 0; });
  run<eve::vmx, std::uint64_t, 2>([](int, int) { return 1; });
};

}
