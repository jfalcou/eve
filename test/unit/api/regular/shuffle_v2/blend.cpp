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

// This is enough
template<std::ptrdiff_t N>
constexpr auto
all_blend_patterns_to_test_for(eve::fixed<N>)
{
  return kumi::tuple {
      eve::fix_pattern<N>([](int i, int) { return i % 2; }),
      eve::fix_pattern<N>([](int i, int) { return i % 3 == 0; }),
      eve::fix_pattern<N>([](int i, int) { return i == 0 ? 0 : 1; }),
      eve::fix_pattern<N>([](int i, int) { return i == 0 ? 1 : 0; }),
  };
}

TTS_CASE_TPL("Check blend, generic", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  shuffle_test::named_shuffle2_test<
      /*supports_G_eq_T_Size*/ true>(
      eve::as<T> {},
      eve::blend,
      []<std::ptrdiff_t G>(eve::fixed<G>)
      {
        auto to_test_for = all_blend_patterns_to_test_for(eve::lane<T::size() / G>);
        auto lifted      = kumi::map([](auto x) { return kumi::make_tuple(x); }, to_test_for);
        return lifted;
      });
};

} // namespace
