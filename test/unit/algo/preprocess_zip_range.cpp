//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "algo_test.hpp"

#include <eve/algo/zip_iterator.hpp>

#include <eve/algo/as_range.hpp>
#include <eve/algo/traits.hpp>
#include <eve/algo/ptr_iterator.hpp>

#include <eve/algo/find.hpp>

#include <vector>

TTS_CASE("zip_iterator, preprocess range")
{
  std::vector<int> v1{1, 2, 3};
  std::vector<int> v2{1, 2, 4};
  eve::algo::zip_iterator zf{v1.begin(), v2.begin()};

  auto processed = eve::algo::preprocess_range(eve::algo::traits{}, eve::algo::as_range(zf, v1.end()));

  using ui_it = eve::algo::unaligned_ptr_iterator<int, eve::fixed<eve::expected_cardinal_v<int>>>;
  using zip_ui = eve::algo::zip_iterator<ui_it, ui_it>;
  zip_ui processed_f = processed.begin();
  zip_ui processed_l = processed.end();

  TTS_EQUAL((processed_l - processed_f), 3);

  using v_i = std::vector<int>::iterator;
  using zip_vi = eve::algo::zip_iterator<v_i, v_i>;
  zip_vi back_zf = processed.to_output_iterator(processed_f);
  TTS_EQUAL(back_zf, zf);
}

TTS_CASE("missmatch prototype")
{
  std::vector<int> v1{1, 2, 3, 4};
  std::vector<int> v2{1, 2, 4, 5};

  eve::algo::zip_iterator zf {v1.begin(), v2.begin()};

  auto found = eve::algo::find_if(eve::algo::as_range(zf, v1.end()), [](auto x1_x2) {
    auto [x1, x2] = x1_x2;
    return x1 != x2;
  });

  TTS_EQUAL((found - zf), 2);
  TTS_EQUAL(get<0>(*found), 3);
  TTS_EQUAL(get<1>(*found), 4);
}
