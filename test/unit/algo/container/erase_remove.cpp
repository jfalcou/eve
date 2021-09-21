//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/algo/container/soa_vector.hpp>
#include <eve/algo/remove.hpp>

#include "unit/algo/udt.hpp"

/*
FIX-#971
TTS_CASE("erase/remove idiom in eve")
{
  eve::algo::soa_vector<udt::line2D> lines {
    udt::line2D{ udt::point2D{0, 1}, udt::point2D{1,   2} },
    udt::line2D{ udt::point2D{1, 3}, udt::point2D{2,   2} },
    udt::line2D{ udt::point2D{0, 1}, udt::point2D{4,   5} },
    udt::line2D{ udt::point2D{6, 2}, udt::point2D{-1, -1} }
  };

  udt::point2D bad_start{0, 1};

  TTS_PASS("FIX-#868, then test");

  lines.erase(
    eve::algo::remove_if(lines, [&](eve::wide<udt::line2D> l) {
      return get_start(l) == bad_start;
    }),
    lines.end()
  );
}
*/

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
    eve::algo::remove_if(points, [&](eve::wide<udt::point2D> p) {
      return p == bad;
    }),
    points.end()
  );

  TTS_EQUAL(expected, points);
}
