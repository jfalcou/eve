//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/regular/shuffle/shuffle_v2_test.hpp"

// 8 byte registers are their own thing for android neon only,
// for everything else this is just a subset of bigger registers test

namespace
{

TTS_CASE("shuffle_v2: 8x1")
{
  auto expected_level = [](std::span<const std::ptrdiff_t> p)
  {
    if ( p.size() == 1 ) { return p[0] == eve::na_ ? 1 : 0; }

    // We can do better sometimes but not yet
    if (eve::current_api >= eve::sve || eve::current_api >= eve::vmx) return 3;

    if ( p.size() == 2 ) return 2;
    return -1;
  };

  shuffle_test::run_all<std::uint64_t, 1, 1, shuffle_test::kLen1Tests>(expected_level);
  shuffle_test::run_all<std::uint32_t, 2, 1, shuffle_test::kLen2No0sTests>(expected_level);
};

}
