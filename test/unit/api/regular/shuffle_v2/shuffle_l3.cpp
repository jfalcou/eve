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
using eve::we_;

auto return3 = [](auto...) { return 3; };

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1, std::ptrdiff_t... I>
void
run_any_api(eve::pattern_t<I...> p)
{
  shuffle_test::run<T, N, G>(return3, p);
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run_any_api(eve::pattern_formula auto formula)
{
  run_any_api<T, N, G>(eve::fix_pattern<N>(formula));
}

template<typename T, std::ptrdiff_t G = 1>
void
run_any_api_expected_cardinal(auto pattern)
{
  run_any_api<T, eve::expected_cardinal_v<T>, G>(pattern);
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1>
void
run(auto pattern)
{
  if constexpr( eve::current_api >= api ) { run_any_api<T, N, G>(pattern); }
  else { TTS_PASS(); }
}

template<typename T, std::ptrdiff_t N, std::ptrdiff_t G = 1, std::ptrdiff_t... I>
void
run2_any_api(eve::pattern_t<I...> p)
{
  shuffle_test::run2<T, N, G>(return3, p);
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

// named common patterns ------------------------------

auto blend_every_other = [](int i, int size)
{
  if( i % 2 ) return i + size;
  return i;
};


// any api --------------------------------------------

TTS_CASE("and 0s")
{
  // masking 0s is free for these arches.
  if constexpr( eve::current_api >= eve::avx512 || eve::current_api >= eve::rvv
                || eve::current_api >= eve::sve )
  {
    TTS_PASS();
    return;
  }
  run_any_api_expected_cardinal<std::uint8_t>(
      [](int i, int /*size*/) -> std::ptrdiff_t
      {
        if( i == 3 ) return na_;
        if( i % 5 == 0 ) return we_;
        if( i % 7 == 0 ) return na_;
        return i;
      });
};

// x86 ------------------------------------------------

TTS_CASE("_mm_shuffle_epi8")
{
  run<eve::ssse3, std::uint8_t, 16>(
      eve::pattern<15, na_, 11, we_, 0, 1, 3, 15, 15, 14, 13, 12, 5, 8, 6, 4>);

  auto pattern = [](int i, int) -> std::ptrdiff_t
  {
    int base   = i / 16 * 16;
    int offset = (i + i / 16) % 16;

    if( offset == 3 ) return we_;
    if( offset == 7 ) return na_;

    if( offset == 0 ) return base + 1;
    if( offset == 12 ) return base + 10;

    return base + (offset + 3) % 16;
  };

  run<eve::ssse3, std::uint8_t, 16>(pattern);
  run<eve::avx2, std::uint8_t, 32>(pattern);
  run<eve::avx512, std::uint8_t, 64>(pattern);
};

TTS_CASE("_mm_permutexvar")
{
  run<eve::avx2, std::uint32_t, 8>(eve::pattern<3, 1, 5, we_, 2, 0, 7, 3>);
  run<eve::avx2, std::uint32_t, 8>(eve::pattern<0, 0, 4, 4, we_, 6, 2, 1>);
  run<eve::avx2, std::uint32_t, 8>(eve::pattern<5, we_, 3, 5, 1, 6, 0, 2>);

  run<eve::avx512, std::uint16_t, 32>(
      [](int i, int size) -> std::ptrdiff_t
      {
        if( i == 4 ) return we_;
        if( i < 16 ) return size - 2 * i - 2;
        return size - 2 * (i - 16) - 1;
      });

  run<eve::avx512, std::uint16_t, 32>(
      [](int i, int size) -> std::ptrdiff_t
      {
        if( i == 3 ) return we_;
        return (i * 5 + 5) % size;
      });

  run<eve::avx512, std::uint32_t, 16>(
      eve::pattern<3, 1, 5, we_, 2, 0, 7, 3, 10, 12, 9, 15, 8, 11, 14, 13>);
  run<eve::avx512, std::uint32_t, 16>(
      eve::pattern<0, 0, 4, 4, we_, 6, 2, 1, 8, 10, 12, 14, 9, 11, 13, 15>);

  run<eve::avx512, std::uint64_t, 8>(eve::pattern<3, 1, 5, we_, 2, 0, 7, 3>);
  run<eve::avx512, std::uint64_t, 8>(eve::pattern<0, 0, 4, 4, we_, 6, 2, 1>);
};

TTS_CASE("_mm_blendv_epi8")
{
  if constexpr( eve::current_api >= eve::avx512 )
  {
    TTS_PASS();
    return;
  }

  run2<eve::sse4_1, std::uint8_t, 16>(blend_every_other);
  run2<eve::avx2, std::uint8_t, 32>(blend_every_other);
};

TTS_CASE("_mm_permutex2var")
{
  run2<eve::avx512, std::uint16_t, 8>(eve::pattern<3, 11, 5, we_, 2, 10, 7, 15>);
  run2<eve::avx512, std::uint16_t, 16>(
      [](int i, int size) -> std::ptrdiff_t
      {
        if( i == 4 ) return we_;
        return (i * 3 + 1) % (2 * size);
      });
  run2<eve::avx512, std::uint16_t, 32>(
      [](int i, int size) -> std::ptrdiff_t
      {
        if( i == 4 ) return we_;
        return (i * 3 + 7) % (2 * size);
      });

  run2<eve::avx512, std::uint32_t, 4>(eve::pattern<3, 5, we_, 7>);
  run2<eve::avx512, std::uint32_t, 8>(eve::pattern<3, 11, 5, 13, 2, 10, we_, 15>);
  run2<eve::avx512, std::uint32_t, 16>(
      [](int i, int size) -> std::ptrdiff_t
      {
        if( i == 6 ) return we_;
        return (i * 5 + 3) % (2 * size);
      });

  run2<eve::avx512, std::uint64_t, 4>(eve::pattern<3, 5, we_, 7>);
  run2<eve::avx512, std::uint64_t, 8>(eve::pattern<3, 11, 5, 13, 2, 10, 7, we_>);
};

// arm-neon -------------------------------------------

TTS_CASE("vtbl1_u8(x)")
{
  run<eve::neon, std::uint8_t, 8>(eve::pattern<3, 1, 5, we_, 2, 0, 7, 3>);
  run<eve::neon, std::uint8_t, 8>(eve::pattern<0, 0, 4, 4, we_, 6, 2, 1>);

  run<eve::asimd, std::uint8_t, 16>([](int i, int size)
                                     {
                                       if( i == 4 ) return static_cast<int>(we_);
                                       if( i == 7 ) return static_cast<int>(na_);
                                       return (i * 3 + 2) % size;
                                     });
};

TTS_CASE("neon_bit_select")
{
  run2<eve::neon, std::uint8_t, 8>(blend_every_other);
  run2<eve::neon, std::uint8_t, 16>(blend_every_other);
};


}
