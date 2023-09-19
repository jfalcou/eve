//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/api/regular/shuffle_v2/shuffle_v2_test.hpp"

// 8 byte registers are their own thing for android neon only,
// for everything else this is just a subset of bigger registers test

namespace
{

namespace idxm = eve::detail::idxm;

TTS_CASE("shuffle_v2: 8x1")
{
  auto expected_level = [](std::span<const std::ptrdiff_t> p)
  {
    if ( p.size() == 1 ) { return p[0] == eve::na_ ? 1 : 0; }

    // We can do better sometimes but not yet
    if (eve::current_api >= eve::vmx) return 3;

    if (eve::current_api >= eve::sve)
    {
      if (idxm::is_reverse(p)) return 2;
      if (idxm::matches(p, {1, 0, 3, 2})) return 2;
      return 3;
    }

    if ( p.size() == 2 )
    {
      if (eve::current_api < eve::sse4_1 && idxm::matches(p, {0, eve::na_})) return 3;
      return 2;
    }
    if ( p.size() == 4 )
    {
      if (eve::current_api >= eve::sse2)
      {
        if (!idxm::has_zeroes(p)) return 2;
        return 3;
      }
      if (eve::current_api >= eve::neon)
      {
        if (idxm::is_rotate(p)) return 2;
        if (idxm::is_just_setting_one_zero(p)) return 2;
        if (idxm::matches(p, {1, 0, 3, 2})) return 2;
        if (idxm::matches(p, {3, 2, 1, 0})) return 2;
        if (eve::current_api >= eve::asimd)
        {
          if (idxm::is_just_setting_one_lane(p)) return 2;
        }
        return 3;
      }
    }

    return -1;
  };

  shuffle_test::run_all<std::uint64_t, 1, 1, shuffle_test::kLen1Tests>(expected_level);
  shuffle_test::run_all<std::uint32_t, 2, 1, shuffle_test::kLen2Tests>(expected_level);
  shuffle_test::run_all<std::uint16_t, 4, 1, shuffle_test::kLen4N0Tests>(expected_level);
  //shuffle_test::run_all_4_element_tests<std::uint16_t, 4, 1>(expected_level);
};

}
