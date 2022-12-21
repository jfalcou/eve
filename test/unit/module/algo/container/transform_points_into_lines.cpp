//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include "unit/module/algo/udt.hpp"

#include <eve/module/algo.hpp>

#include <eve/module/core.hpp>
#include <vector>

TTS_CASE("transform points into vertical lines")
{
  eve::algo::soa_vector<udt::point2D> starts{
    udt::point2D{0, 1},
    udt::point2D{1, 1},
    udt::point2D{2, 2},
    udt::point2D{3, 3},
  };

  std::vector<std::int32_t> lengths {
    1, 2, 3, 5
  };

  eve::algo::soa_vector<udt::line2D> expected{
    udt::line2D{udt::point2D{0, 1}, udt::point2D{0, 1 - 1}},
    udt::line2D{udt::point2D{1, 1}, udt::point2D{1, 1 - 2}},
    udt::line2D{udt::point2D{2, 2}, udt::point2D{2, 2 - 3}},
    udt::line2D{udt::point2D{3, 3}, udt::point2D{3, 3 - 5}},
  };

  eve::algo::soa_vector<udt::line2D> actual(starts.size());

  eve::algo::transform_to(eve::algo::views::zip(starts, lengths), actual,
    [](auto start_l) {
      auto [start, l] = start_l;
      auto end = start;
      get_y(end) -= l;
      return eve::zip(start, end);
  });

  TTS_EQUAL(expected, actual);
};
