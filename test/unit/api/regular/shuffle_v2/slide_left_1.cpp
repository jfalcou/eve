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

template<typename T, int G>
auto
test_indexes()
{
  // still will be tested through G == 1
  if constexpr( G > 1 ) return kumi::tuple {eve::index<1>};
  // just reducing compile times a bit
  else if constexpr ( !eve::unsigned_simd_value<T> ) return kumi::tuple{eve::index<1>};
  else
  {
    return []<std::size_t... i>(std::index_sequence<i...>)
    { return kumi::tuple {eve::index<i>...}; }(std::make_index_sequence<T::size()> {});
  }
}

#if 0
TTS_CASE("Slide left 1, example") {
  using w_i = eve::wide<int, eve::fixed<4>>;
  w_i x{1, 2, 3, 4};
  TTS_EQUAL(eve::slide_left2(x, eve::index<1>), w_i({2, 3, 4, 0}));
};
#endif

#if 0
TTS_CASE("Explicit") {
  // constexpr auto na_ = eve::na_;
  using w_i = eve::wide<std::uint32_t, eve::fixed<16>>;
  w_i x {[](int i, int) { return i + 1; }};
  auto [y, l] = eve::shuffle_v2_core(x, eve::pattern<5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1>);
  TTS_EQUAL(l(), 4);
  (void)y;
#if 0
  TTS_EQUAL(y, w_i({2, 0}));

  TTS_EQUAL(eve::slide_left2.level(eve::as<w_i>{}, eve::fixed<1>{}, eve::index<1>), 2);
  (void)y;

  auto [y, l] = eve::shuffle_v2_core(x, eve::pattern<7, na_, na_, na_, na_, na_, na_, na_>);
  TTS_EQUAL(y, w_i({8, 0, 0, 0, 0, 0, 0, 0}));
  TTS_EQUAL(l(), 4);
#endif
};
#endif

TTS_CASE_TPL("Check slide_left, 1 arg, generic", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  static constexpr std::ptrdiff_t reg_size = sizeof(eve::element_type_t<T>) * T::size();
  if constexpr( eve::current_api <= eve::sse4_2 || eve::current_api >= eve::neon ||
    ( eve::current_api >= eve::avx2 && reg_size <= 32 ) ||
    ( eve::current_api >= eve::avx512 && sizeof(eve::element_type_t<T>) >= 2 ) ||
    ( eve::current_api >= eve::sve) )
  {
    shuffle_test::named_shuffle1_test<
        /*supports_G_eq_T_Size*/ true>(eve::as<T> {},
                                       eve::slide_left2,
                                       []<std::ptrdiff_t G>(eve::fixed<G>)
                                       {
                                         auto idxs   = test_indexes<T, G>();
                                         auto lifted = kumi::map(
                                             [](auto x) { return kumi::make_tuple(x); }, idxs);
                                         return lifted;
                                       });
  }
  else { TTS_PASS(); }
};

}
