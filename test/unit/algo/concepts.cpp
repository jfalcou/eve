//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "unit/algo/algo_test.hpp"

#include <eve/algo/concepts.hpp>

#include <eve/algo/ptr_iterator.hpp>
#include <eve/algo/zip.hpp>

#include <vector>

TTS_CASE("concepts, value type")
{
  TTS_TYPE_IS(eve::algo::value_type_t<int*>, int);
  TTS_TYPE_IS(eve::algo::value_type_t<const int*>, int);

  using u_p = eve::algo::unaligned_ptr_iterator<int const, eve::fixed<2>>;
  TTS_TYPE_IS(eve::algo::value_type_t<u_p>, int);

  std::vector<int> v1, v2;

  TTS_TYPE_IS(eve::algo::value_type_t<decltype(v1)>, int);
  TTS_TYPE_IS((eve::algo::value_type_t<decltype(eve::algo::zip(v1, v2))>),
               (kumi::tuple<int, int>));
}

TTS_CASE("concepts, relaxed")
{
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_iterator<int*>);
  TTS_CONSTEXPR_EXPECT_NOT(eve::algo::relaxed_range<int*>);
  TTS_CONSTEXPR_EXPECT(eve::algo::relaxed_range<std::vector<int>>);
}
