//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/regular/shuffle_v2/shuffle_v2_test.hpp"

/*
 * These tests should be supported for all platforms and migrated
 * into appropriate nxm files.
 */

namespace
{

constexpr auto expect_l2 = [](std::span<const std::ptrdiff_t> p)
{
  if( p.size() == 1 ) return p[0] == eve::na_ ? 1 : 0;
  return 2;
};

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
[[maybe_unused]] void
shuffle_l0_test()
{
  if constexpr( eve::current_api < api ) TTS_PASS();
  else shuffle_test::run<T, N, G, I...>(expect_l2);
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
[[maybe_unused]] void
shuffle_l0_2_test()
{
  if constexpr( eve::current_api < api ) TTS_PASS();
  else shuffle_test::run2<T, N, G, I...>(expect_l2);
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, auto tests>
[[maybe_unused]] void
shuffle_l0_all()
{
  if constexpr( eve::current_api < api ) TTS_PASS();
  else shuffle_test::run_all<T, N, G, tests>(expect_l2);
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, auto tests>
[[maybe_unused]] void
shuffle_l0_2_all()
{
  if constexpr( eve::current_api < api ) TTS_PASS();
  else shuffle_test::run2_all<T, N, G, tests>(expect_l2);
}

#if defined(EVE_HW_X86)
TTS_CASE("Perfect shuffle, x86, 16 bytes")
{
  // 16x1
  shuffle_l0_all<eve::sse2, std::uint64_t, 2, 2, shuffle_test::kLen1Tests>();

  // 8x2
  shuffle_l0_all<eve::sse2, std::uint64_t, 2, 1, shuffle_test::kLen2No0sTests>();
  // < sse4.1 requires a mask for set 0
  shuffle_l0_test<eve::sse2, std::uint64_t, 2, 1, 0, eve::na_>();
  shuffle_l0_test<eve::sse2, std::uint64_t, 2, 1, eve::na_, 0>();
  shuffle_l0_test<eve::sse2, std::uint64_t, 2, 1, 1, eve::na_>();
  shuffle_l0_all<eve::sse4_1, std::uint64_t, 2, 1, shuffle_test::kLen20sTests>();

  shuffle_l0_all<eve::sse2, std::uint32_t, 4, 1, shuffle_test::kLen4No0Tests_IndependentHalves>();
  shuffle_l0_all<eve::sse2, std::uint32_t, 4, 1, shuffle_test::kLen4N0Tests_CrossLane>();

  // rotate
  shuffle_l0_all<eve::sse3, std::uint16_t, 8, 1, shuffle_test::kRotate8>();
  shuffle_l0_all<eve::sse3, std::uint8_t, 16, 1, shuffle_test::kRotate16>();
};

TTS_CASE("Perfect shuffle, x86, 16x2")
{
  shuffle_l0_2_all<eve::sse2, std::uint64_t, 2, 2, shuffle_test::kLen1x2Tests>();

  // 8x2x2
  shuffle_l0_2_test<eve::sse2, std::uint64_t, 2, 1, eve::na_, 0>();
  shuffle_l0_2_test<eve::sse2, std::uint64_t, 2, 1, 2, eve::na_>();
  shuffle_l0_2_all<eve::sse2, std::uint64_t, 2, 1, shuffle_test::kLen2x2_No0sTests>();
  shuffle_l0_2_all<eve::sse2, std::uint64_t, 2, 1, shuffle_test::kLen2x2_No0sTests>();

  // 4x4x2 blend
  shuffle_l0_2_all<eve::sse4_1, std::uint32_t, 4, 1, shuffle_test::kLen4x2_No0sBlendTests>();

  // 2x8x2 blend
#  if 0 // FIX-1617 - enable `_mm_blend_epi16`
  shuffle_l0_2_all<eve::sse4_1, std::uint16_t, 4, 1, shuffle_test::kLen2x8x2_No0sBlendTests>();
#  endif
};

TTS_CASE("Perfect shuffle, x86, 32 bytes")
{
  // 32x1
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 4, shuffle_test::kLen1Tests>();

  // 16x2
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 2, shuffle_test::kLen2No0sTests>();
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 2, shuffle_test::kLen20sTests>();

  // 8x4 in havles
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 1, shuffle_test::kLen4No0Tests_IndependentHalves>();
  shuffle_l0_all<eve::avx2, std::uint64_t, 4, 1, shuffle_test::kLen4N0Tests_CrossLane>();

  // 4x8 in halves, repeating
  {
    constexpr auto cases = shuffle_test::concat(
        shuffle_test::matchRightLane(shuffle_test::kLen4No0Tests_IndependentHalves),
        shuffle_test::matchRightLane(shuffle_test::kLen4N0Tests_CrossLane));

    shuffle_l0_all<eve::avx, std::uint32_t, 8, 1, cases>();
  }

  // rotate 128
  {
    constexpr auto r8  = shuffle_test::matchRightLane(shuffle_test::kRotate8);
    constexpr auto r16 = shuffle_test::matchRightLane(shuffle_test::kRotate16);

    shuffle_l0_all<eve::avx2, std::uint16_t, 16, 1, r8>();
    shuffle_l0_all<eve::avx2, std::uint8_t, 32, 1, r16>();
  }
};

// No new patterns but just to see that other behavour works as expected
TTS_CASE("Perfect shuffle, x86, sanity checks")
{
  shuffle_l0_test<eve::avx, float, 8, 2, 0, 0, 2, 2>();
  shuffle_l0_test<eve::avx, std::int64_t, 4, 1, 0, 0, 2, 2>();
  shuffle_l0_test<eve::avx, double, 4, 1, 0, 0, eve::we_, 2>();
  shuffle_l0_test<eve::avx, double, 4, 1, eve::we_, 0, 2, 2>();

  shuffle_l0_test<eve::sse2, std::uint16_t, 8, 1, 4, 5, 6, 7, 0, 1, 2, 3>();

  // pattern got upscaled properly
  shuffle_l0_test<eve::avx, float, 4, 1, 2, 3, 0, 1>();
};
#endif

}
