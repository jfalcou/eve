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

namespace idxm = eve::detail::idxm;

TTS_CASE("shuffle_v2: 64x1")
{
  if constexpr (eve::expected_cardinal_v<std::uint64_t> < 8)
  {
    TTS_PASS();
    // This needs a 2 reg shuffle we do not suport yet
    return;
  }
  auto expected_level = [](std::span<const std::ptrdiff_t> p)
  {
    // We can do better sometimes but not yet
    if( eve::current_api >= eve::sve ) {
      if (idxm::matches(p, {1, 0})) return 2;
      if (idxm::matches(p, {3, 0, 1, 2})) return 2;
      if (idxm::matches(p, {1, 2, 3, 0})) return 2;
      return 3;
    }
    return 2;
  };

  shuffle_test::run_all<std::uint64_t, 8, 8, shuffle_test::kLen1Tests>(expected_level);
  shuffle_test::run_all<std::uint64_t, 8, 4, shuffle_test::kLen2Tests>(expected_level);

  shuffle_test::run_all<std::uint64_t, 8, 2, shuffle_test::kLen4N0Tests>(expected_level);
};

}
