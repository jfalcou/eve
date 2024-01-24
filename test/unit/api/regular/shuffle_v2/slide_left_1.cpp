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

template<int N, int G>
auto
test_indexes()
{
  // still will be tested through G == 1
  if constexpr( G > 1 ) return kumi::tuple {eve::index<1>};
  else
  {
    return []<std::size_t... i>(std::index_sequence<i...>)
    { return kumi::tuple {eve::index<i>...}; }(std::make_index_sequence<N> {});
  }
}

#if 0

TTS_CASE("Slide left 1, example") {
  using w_i = eve::wide<int, eve::fixed<4>>;
  w_i x{1, 2, 3, 4};
  TTS_EQUAL(eve::slide_left2(x, eve::index<1>), w_i({2, 3, 4, 0}));
};

TTS_CASE("Explicit") {
  using w_i = eve::wide<std::uint32_t, eve::fixed<8>>;
  w_i x{1, 2, 3, 4, 5, 6, 7, 8};
  //constexpr auto na_ = eve::na_;
  auto y = eve::slide_left2(x, eve::index<7>);
  TTS_EQUAL(y, w_i({8, 0, 0, 0, 0, 0, 0, 0}));
  //TTS_EQUAL(l(), 2);
};
#endif

TTS_CASE_TPL("Check slide_left, 1 arg, generic", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( eve::current_api <= eve::sse4_2 )
  {
    shuffle_test::named_shuffle1_test<
        /*supports_G_eq_T_Size*/ true>(eve::as<T> {},
                                       eve::slide_left2,
                                       []<std::ptrdiff_t G>(eve::fixed<G>)
                                       {
                                         auto idxs   = test_indexes<T::size(), G>();
                                         auto lifted = kumi::map(
                                             [](auto x) { return kumi::make_tuple(x); }, idxs);
                                         return lifted;
                                       });
  }
  else { TTS_PASS(); }
};

}
