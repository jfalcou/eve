//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/algo.hpp>

#include "unit/module/algo/udt.hpp"

TTS_CASE("erase/remove idiom in eve")
{
  eve::algo::soa_vector<udt::line2D> lines {
    udt::line2D{ udt::point2D{0, 1}, udt::point2D{1,   2} },
    udt::line2D{ udt::point2D{1, 3}, udt::point2D{2,   2} },
    udt::line2D{ udt::point2D{0, 1}, udt::point2D{4,   5} },
    udt::line2D{ udt::point2D{6, 2}, udt::point2D{-1, -1} }
  };

  eve::algo::soa_vector<udt::line2D> expected {
    udt::line2D{ udt::point2D{1, 3}, udt::point2D{2,   2} },
    udt::line2D{ udt::point2D{6, 2}, udt::point2D{-1, -1} }
  };

  udt::point2D bad_start{0, 1};

  lines.erase(
    eve::algo::remove_if(lines, [&](eve::nofs_wide<udt::line2D> l) {
      return get_start(l) == bad_start;
    }),
    lines.end()
  );

  TTS_EQUAL(expected, lines);
};

TTS_CASE("erase/remove idiom in eve")
{
  eve::algo::soa_vector<udt::point2D> points {
    udt::point2D{0, 1}, udt::point2D{1, 2}, udt::point2D{1, 3}
  };

  udt::point2D bad{0, 1};

  eve::algo::soa_vector<udt::point2D> expected {
    points.get(1), points.get(2)
  };

  points.erase(
    eve::algo::remove_if(points, [&](eve::nofs_wide<udt::point2D> p) {
      return p == bad;
    }),
    points.end()
  );

  TTS_EQUAL(expected, points);
};
