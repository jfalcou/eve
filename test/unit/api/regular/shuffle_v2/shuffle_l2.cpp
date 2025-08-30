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

template<typename T, std::ptrdiff_t N, std::ptrdiff_t... I>
void
run_any_api(eve::pattern_t<I...> p)
{
  shuffle_test::run<T, N, 1>(return2, p);
}

template<typename T, std::ptrdiff_t N>
void
run_any_api(eve::pattern_formula auto formula)
{
  run_any_api<T, N>(eve::fix_pattern<N>(formula));
}

template<auto api, typename T, std::ptrdiff_t N>
void
run(auto pattern)
{
  if constexpr( eve::current_api >= api ) { run_any_api<T, N>(pattern); }
  else { TTS_PASS(); }
}

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

TTS_CASE("_mm_shufflelo_epi16/_mm256_shufflehi_epi16")
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

TTS_CASE("_mm256_permute4x64_epi64 / _mm512_permutex_epi64")
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

}
