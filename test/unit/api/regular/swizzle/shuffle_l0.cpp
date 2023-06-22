//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/regular/swizzle/shuffle_test.hpp"

namespace
{

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, std::ptrdiff_t... I>
[[maybe_unused]] void
shuffle_l0_test()
{
  shuffle_test::run<api, T, N, G, I...>(eve::shuffle_l0);
}

template<auto api, typename T, std::ptrdiff_t N, std::ptrdiff_t G, auto tests>
[[maybe_unused]] void
shuffle_l0_all()
{
  shuffle_test::run_all<api, T, N, G, tests>(eve::shuffle_l0);
}

#if defined(EVE_HW_X86)
TTS_CASE("Perfect shuffle, x86, 16 bytes")
{
  // 16x1
  shuffle_l0_all<eve::sse2, double, 2, 2, shuffle_test::kLen1Tests>();
  shuffle_l0_all<eve::sse2, std::uint64_t, 2, 2, shuffle_test::kLen1Tests>();

  // 8x2
  shuffle_l0_all<eve::sse2, double, 2, 1, shuffle_test::kLen2No0sTests>();
  shuffle_l0_all<eve::sse2, std::uint64_t, 2, 1, shuffle_test::kLen2No0sTests>();
};

TTS_CASE("Perfect shuffle, x86, 32 bytes")
{
  // 32x1
  shuffle_l0_all<eve::avx, double, 4, 4, shuffle_test::kLen1Tests>();
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 4, shuffle_test::kLen1Tests>();

  // 16x2
  shuffle_l0_all<eve::avx, double, 4, 2, shuffle_test::kLen2No0sTests>();
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 2, shuffle_test::kLen2No0sTests>();
  shuffle_l0_all<eve::avx, double, 4, 2, shuffle_test::kLen20sTests>();
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 2, shuffle_test::kLen20sTests>();

  // 8x4 in havles
  shuffle_l0_all<eve::avx, double, 4, 1, shuffle_test::kLen4No0Tests_IndependentHalves>();
  shuffle_l0_all<eve::avx, std::uint64_t, 4, 1, shuffle_test::kLen4No0Tests_IndependentHalves>();

  shuffle_l0_all<eve::avx2, double, 4, 1, shuffle_test::kLen4N0Tests_CrossLane>();
  shuffle_l0_all<eve::avx2, std::uint64_t, 4, 1, shuffle_test::kLen4N0Tests_CrossLane>();
};

// No new patterns but just to see that other behavour works as expected
TTS_CASE("Perfect shuffle, x86, sanity checks")
{
  shuffle_l0_test<eve::avx, std::uint32_t, 8, 1, 0, 1, 2, 3, 4, 5, 6, 7>();
  shuffle_l0_test<eve::avx, float, 8, 2, 0, 0, 2, 2>();
  shuffle_l0_test<eve::avx, std::int64_t, 4, 1, 0, 0, 2, 2>();
  shuffle_l0_test<eve::avx, double, 4, 1, 0, 0, eve::we_, 2>();
  shuffle_l0_test<eve::avx, double, 4, 1, eve::we_, 0, 2, 2>();

  shuffle_l0_test<eve::sse2, std::uint16_t, 8, 1, 4, 5, 6, 7, 0, 1, 2, 3>();

  // pattern got upscaled properly
  shuffle_l0_test<eve::avx, float, 4, 1, 2, 3, 0, 1>();

  // To see that sfiane works. Reverting 16 chars on x86 needs a mask - so
  // not perfect shuffle.
  TTS_CONSTEXPR_EXPECT_NOT(
      (std::invocable<decltype(eve::shuffle_l0),
                      eve::wide<std::int8_t, eve::fixed<16>>,
                      eve::fixed<1>,
                      eve::pattern_t<15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0>>

       ));
};
#endif

#if defined(EVE_HW_ARM)
TTS_CASE("Perfect shuffle, arm neon, 8 bytes")
{
  // 8x1
  shuffle_l0_all<eve::neon, float, 2, 2, shuffle_test::kLen1Tests>();
  shuffle_l0_all<eve::neon, std::uint64_t, 1, 1, shuffle_test::kLen1Tests>();

  // 4x2
  shuffle_l0_all<eve::neon, float, 2, 1, shuffle_test::kLen2No0sTests>();
  shuffle_l0_all<eve::neon, std::uint32_t, 2, 1, shuffle_test::kLen2No0sTests>();
  shuffle_l0_all<eve::neon, float, 2, 1, shuffle_test::kLen20sTests>();
  shuffle_l0_all<eve::neon, std::uint32_t, 2, 1, shuffle_test::kLen20sTests>();
};

TTS_CASE("Perfect shuffle, arm neon, sanity checks")
{
  shuffle_l0_test<eve::avx, std::uint16_t, 4, 1, 2, 3, 2, 3>();
};
#endif

}
