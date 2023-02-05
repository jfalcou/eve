//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "unit/module/algo/algo_test.hpp"

#include <eve/module/algo.hpp>

#include <vector>

TTS_CASE("concepts, relaxed")
{
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_iterator<int*>);
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_iterator<eve::nofs_aligned_ptr<int>>);
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_iterator<int const*>);
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_iterator<eve::nofs_aligned_ptr<int const>>);
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_iterator<eve::nofs_aligned_ptr<int const> const&>);

  TTS_CONSTEXPR_EXPECT_NOT(eve::algo::relaxed_range<int*>);
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_range<std::vector<int>>);
};

TTS_CASE("concepts, types_to_consider_for")
{
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<int*>,             kumi::tuple<int>);
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<int const*>,       kumi::tuple<int>);
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<std::vector<int>>, kumi::tuple<int>);

  std::vector<int>   v_i;
  std::vector<short> v_s;

  auto c_v_i_r = eve::algo::views::convert(v_i,         eve::as<double>{});
  auto c_v_i_i = eve::algo::views::convert(v_i.begin(), eve::as<double>{});


  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<decltype(c_v_i_r)>, (kumi::tuple<double, int>));
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<decltype(c_v_i_i)>, (kumi::tuple<double, int>));


  auto zip_s_i_i = eve::algo::views::zip(v_s, v_i, v_i);

  // This should probably be a type set but w/e
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<decltype(zip_s_i_i)        >, (kumi::tuple<short, int, int>));
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<decltype(zip_s_i_i.begin())>, (kumi::tuple<short, int, int>));

  auto zip_c_i_s = eve::algo::views::zip(c_v_i_r, v_s);

  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<decltype(zip_c_i_s)        >, (kumi::tuple<double, int, short>));
  TTS_TYPE_IS(eve::algo::types_to_consider_for_t<decltype(zip_c_i_s.begin())>, (kumi::tuple<double, int, short>));
};
