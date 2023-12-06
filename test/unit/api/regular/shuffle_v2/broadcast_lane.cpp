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

template<int NumIdxs>
auto
test_indexes()
{
  // reducing compile times
  if constexpr ( eve::current_api >= eve::sve ) return kumi::tuple{eve::index<0>};
  else if constexpr ( NumIdxs == 1) return kumi::tuple{eve::index<0>};
  else if constexpr ( NumIdxs == 2 ) return kumi::tuple{eve::index<0>, eve::index<1>};
  else return kumi::tuple{eve::index<1>, eve::index<NumIdxs - 1>};
}

TTS_CASE_TPL("Check broadcast lane, generic", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  shuffle_test::named_shuffle1_test<
      /*supports_G_eq_T_Size*/ true>(eve::as<T> {},
                                     eve::broadcast_lane,
                                     []<std::ptrdiff_t G>(eve::fixed<G>)
                                     {
                                       auto idxs = test_indexes<T::size() / G>();
                                       auto lifted    = kumi::map(
                                           [](auto x) { return kumi::make_tuple(x); }, idxs);
                                       return lifted;
                                     });
};

}
