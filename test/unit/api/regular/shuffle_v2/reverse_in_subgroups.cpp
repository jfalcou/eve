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

template<int MaxPow>
auto
all_subgroups()
{
  constexpr auto ssz = std::bit_width(std::size_t(MaxPow));

  // On sse2 it's cheap enough to compile everything
  if constexpr( eve::current_api == eve::sse2 )
  {
    return []<std::size_t... i>(std::index_sequence<i...>)
    { return kumi::tuple {eve::lane<1 << i>...}; }(std::make_index_sequence<ssz> {});
  }
  else
  {
    // removing some cases to reduce compile times
    if constexpr( ssz == 1 ) { return kumi::tuple {eve::lane<1>}; }
    else if constexpr( ssz < 3 ) { return kumi::tuple {eve::lane<2>}; }
    else
    {
      // We can go 0 to ssz but we want to remove:
      // i = 0, i = 1, i = T::size()
      return []<std::size_t... i>(std::index_sequence<i...>)
      { return kumi::tuple {eve::lane<1 << (i + 2)>...}; }(std::make_index_sequence<ssz - 3> {});
    }
  }
}

TTS_CASE_TPL("Check reverse in subgroups, generic", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  shuffle_test::named_shuffle1_test<
      /*supports_G_eq_T_Size*/ true>(eve::as<T> {},
                                     eve::reverse_in_subgroups,
                                     []<std::ptrdiff_t G>(eve::fixed<G>)
                                     {
                                       auto subgroups = all_subgroups<T::size() / G>();
                                       auto lifted    = kumi::map(
                                           [](auto x) { return kumi::make_tuple(x); }, subgroups);
                                       return lifted;
                                     });
};

} // namespace
